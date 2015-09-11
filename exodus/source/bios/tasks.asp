; tasks.asp
;
; Exodus BIOS related task functions
;






    initialize_TASKING      PROC
    ; This routine is initializes the tasking sub-system.  It is called during bootup initialization and is only called once.
    ; After this routine is called, all Exodus Tasking features are fully available.
    ;
    ; Upon entry:   Nothing
    ;
    ; Upon exit:    The tasking subsystem is fully initialized
    ;
        pushad
        push    ds


      ;; Initialize header
        mov     eax,_sTASK_SYSTEM
        mov     ds,eax
        mov     dword ptr ds:[_TASK_SYSTEM_NEXT_OFFSET],_TASK_ENTRY_LENGTH + (_FIRST_TASK_ENTRY*2)
        mov     word ptr  ds:[_TASK_SYSTEM_NEXT_HANDLE],100
        mov     word ptr  ds:[_TASK_SYSTEM_CURRENT_TASK_TSS],_sEXODUS_TSS
        mov     dword ptr ds:[_TASK_SYSTEM_CURRENT_TASK_OFFSET],_FIRST_TASK_ENTRY
        mov     dword ptr ds:[_TASK_SYSTEM_TOTAL_ENTRIES_BASE_0],1


      ;; Initialize the structure for the currently executing task (created at bootup)
        mov     edi,_FIRST_TASK_ENTRY
        mov     word ptr  ds:[edi+_TASK_ENTRY_HANDLE],1
        mov     word ptr  ds:[edi+_TASK_ENTRY_GDT_TSS],_sEXODUS_TSS
        mov     word ptr  ds:[edi+_TASK_ENTRY_GDT_LDT],0ffffh
        mov     word ptr  ds:[edi+_TASK_ENTRY_SELECTOR_OBJECTS],_sEXODUS_OBJECTS
        mov     word ptr  ds:[edi+_TASK_ENTRY_FOCUS_BO],-1
        mov     word ptr  ds:[edi+_TASK_ENTRY_FOCUS_O],-1
        mov     byte ptr  ds:[edi+_TASK_ENTRY_TICKS],1
        mov     byte ptr  ds:[edi+_TASK_ENTRY_MODE],_LINEAR
        mov     word ptr  ds:[edi+_TASK_ENTRY_USES_FPU],1
        mov     dword ptr ds:[edi+_TASK_ENTRY_TSS_LINEAR_OFFSET],_sEXODUS_TSS_base
        mov     byte ptr  ds:[edi+_TASK_ENTRY_TICKS_LEFT],1


      ;; Initialize the entry for the Exodus slave task
        add     edi,_FIRST_TASK_ENTRY
        mov     word ptr  ds:[edi+_TASK_ENTRY_HANDLE],2
        mov     word ptr  ds:[edi+_TASK_ENTRY_GDT_TSS],_sEXODUS_SLAVE_TSS
        mov     word ptr  ds:[edi+_TASK_ENTRY_GDT_LDT],0ffffh
        mov     word ptr  ds:[edi+_TASK_ENTRY_SELECTOR_OBJECTS],-1
        mov     word ptr  ds:[edi+_TASK_ENTRY_FOCUS_BO],-1
        mov     word ptr  ds:[edi+_TASK_ENTRY_FOCUS_O],-1
        mov     byte ptr  ds:[edi+_TASK_ENTRY_TICKS],1
        mov     byte ptr  ds:[edi+_TASK_ENTRY_MODE],_SUSPENDED OR _SLAVE
        mov     word ptr  ds:[edi+_TASK_ENTRY_USES_FPU],1
        mov     dword ptr ds:[edi+_TASK_ENTRY_TSS_LINEAR_OFFSET],_sEXODUS_SLAVE_TSS_base
        mov     byte ptr  ds:[edi+_TASK_ENTRY_TICKS_LEFT],1


      ;; Initialize the object space for this task
        mov     eax,_sEXODUS_OBJECTS
        callf   iOBJECT_initialize_object_space


      ;; Initialize the regs and addresses to use for the _sTASK_SWITCH_TSS
        mov     ebx,_sALL_MEM
        mov     ds,ebx
        mov     esi,_sTASK_SWITCH_TSS_base
      ; Right now, ds:[esi] - far ptr to TSS base
      ; Segment registers
        mov     ebx,_sTASK_SYSTEM
        mov     dword ptr ds:[esi+_TSS_DS],ebx
        mov     dword ptr ds:[esi+_TSS_ES],ebx
        movzx   ebx,cs:data_segment
        mov     dword ptr ds:[esi+_TSS_FS],ebx
        mov     ebx,_sALL_MEM
        mov     dword ptr ds:[esi+_TSS_GS],ebx
      ; Where cs:eip starts
        mov     ebx,cs
        mov     dword ptr ds:[esi+_TSS_CS],ebx
        mov     ebx,offset invTASK_switch_task
        mov     dword ptr ds:[esi+_TSS_EIP],ebx
      ; Stack
        mov     ebx,_sTASK_STACK
        mov     dword ptr ds:[esi+_TSS_SS],ebx
        mov     dword ptr ds:[esi+_TSS_ESP],_sTASK_STACK_limit

        pop     ds
        popad
        ret
    initialize_TASKING      ENDP




    ; iTASK_mouse_interface()
    ; invTASK_adjust_mouse_coordinates()
    INCLUDE mouse.asp




    iTASK_prevent_task_switch       PROC
    ; This routine is called prior to doing something that might take a period of time
    ;
    ; Upon entry:   Nothing
    ;
    ; Upon exit:    Task switching is temporarily disabled
    ;
        retf
    iTASK_prevent_task_switch       ENDP




    iTASK_allow_task_switch     PROC
    ; This routine is called when it's once again safe to allow task switching. :)
    ;
    ; Upon entry:   Nothing
    ;
    ; Upon exit:    Task switching is enabled
    ;
        retf
    iTASK_allow_task_switch     ENDP




    TASK_set_focus      PROC
    ; This routine is used to set focus to a particular task
    ;
    ; Upon entry:   ax - handle
    ;
    ; Upon exit:    Focus is set to that task (if valid)
    ;
        push    ds
        push    ebx

        callf   iTASK_locate_handle
        .IF (carry?)
          ; It wasn't found
            jmp     just_quit
        .ENDIF
      ; Right now, gs:[edi] - far ptr to this task

      ;; Update the task structure
        mov     ebx,_sTASK_SYSTEM
        mov     ds,ebx
        mov     dword ptr ds:[_TASK_SYSTEM_FOCUS_TASK_OFFSET],edi

      ;; Redraw the object's on this task
        callf   iOBJECT_redraw_task

      just_quit:
        pop     ebx
        pop     ds
        retf
    TASK_set_focus      ENDP




    TASK_read_events        PROC
    ; This routine is called from various programs to indicate that linear processing should be terminated for the moment.
    ; Only system events will trigger code execution, such as a mouse clicking on a button
    ;
    ; Upon entry:   ax - task handle
    ;
    ; Upon exit:    This function will only return control after TASK_cancel_read_events() is called.
    ;               Control is never REQUIRED to continue.  The task can be run and executed entirely from objects.
    ;
        mov     ebx,_sTASK_SYSTEM
        mov     ds,ebx
        mov     ebx,dword ptr ds:[_TASK_SYSTEM_CURRENT_TASK_OFFSET]
        mov     al,byte ptr ds:[ebx+_TASK_ENTRY_MODE]
        .IF (al == _LINEAR)
          ; They're currently in linear mode, so we can begin read events
            mov     byte ptr ds:[ebx+_TASK_ENTRY_MODE],_READ_EVENTS
        .ENDIF
        jmp     TASK_release_timeslice

      ; Note, program flow will never reach this point so there's no RETF
    TASK_read_events        ENDP




    TASK_cancel_read_events     PROC
    ; This routine is called to cancel a particular task's previous TASK_read_events() call.  It returns control to the linear
    ; point after the call to TASK_read_events()
    ;
    ; Upon entry:   Nothing
    ;
    ; Upon exit:    This function does not return control to the calling program.  It terminates that thread and returns
    ;               control to the instruction immediately after the previous TASK_read_events() call
    ;
      ; Note, program flow will never reach this point so there's no RETF
    TASK_cancel_read_events     ENDP




    TASK_release_timeslice      PROC
    ; This routine is used to release a timeslice
    ;
    ; Upon entry:   The stack is arranged as below
    ;
    ; Upon exit:    The timeslice has resumed
    ;
        cli
        callg   _sTASK_SWITCH_TASK_GATE
      ; Note, program flow will only return here when this task gets its next timeslice
        sti
        retf
    TASK_release_timeslice      ENDP




    Exodus_TASK_release_timeslice       PROC
    ; This routine is called only from Exodus and only during idle time.
    ; It was added to wait for an interrupt and then release its time slice.
    ;
    ; Upon entry:   Nothing
    ;
    ; Upon exit:    The next interrupt has occurred
    ;
      ; Wait for the next interrupt
        hlt

      ; Switch tasks
        cli
        callg   _sTASK_SWITCH_TASK_GATE
      ; Note, program flow will only return here when this task gets its next timeslice
        sti
        retf
    Exodus_TASK_release_timeslice       ENDP




    iTASK_kbd_interface     PROC
    ; This routine is used to take a key that was input and direct it to the appropriate task's input buffer
    ;
    ; Upon entry:   eax - key that was pressed
    ;               ebx - keyboard flags
    ;
    ; Upon exit:    The key is stored and control is returned
    ;
        retf
    iTASK_kbd_interface     ENDP




    iTASK_locate_handle     PROC
    ; This routine is used to verify that a particular handle is valid and to locate it
    ;
    ; Upon entry:   ax - handle to search for
    ;
    ; Upon exit:    gs:[edi] - far ptr
    ;
        pushad

        mov     ebx,_sTASK_SYSTEM
        mov     gs,ebx
        mov     edi,_FIRST_TASK_ENTRY
        .WHILE (edi < dword ptr gs:[_TASK_SYSTEM_NEXT_OFFSET])
            .IF (word ptr gs:[edi] == ax)
              ; This is it
                mov     dword ptr ss:[esp+00],edi
                clc
                jmp     quit
            .ENDIF
            add     edi,_TASK_ENTRY_LENGTH
        .ENDW
      ; It was not found
        stc

      quit:
        popad
        retf
    iTASK_locate_handle     ENDP




    invTASK_switch_task     PROC
    ; This routine is called from a task gate.  It is known that a task switch is required.
    ;               ⁄ƒƒƒø
    ; Upon entry:   ¥CLI≥ has been issued and will remain in effect throughout this code
    ;               ¿√√√Ÿ
    ;
    ;               All of the previous task's registers have been saved into their TSS
    ;               Our TSS loads the following constants:
    ;                   ds,es - _sTASK_SYSTEM
    ;                   fs - data_segment
    ;                   gs - _sALL_MEM
    ;
    ; Upon exit:    The task is switched to the next one
    ;
      ;;---------------------------
      ;; ⁄ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒø
      ;; ¥ Search LINEAR ≥ Here we look for tasks that are valid, and marked _LINEAR_MODE.
      ;; ¿√√√√√√√√√√√√√√√Ÿ We do a top-down search from whatever the current location is
      ;;                   toward the end of the task chain.  If there are no more tasks
      ;;                   at the end of the chain we cycle back to the beginning.
      ;;
      ;;
    task_switch_start:
        mov     ecx,dword ptr ds:[_TASK_SYSTEM_TOTAL_ENTRIES_BASE_0]
        mov     esi,dword ptr ds:[_TASK_SYSTEM_CURRENT_TASK_OFFSET]
      linear_top:
        add     esi,_TASK_ENTRY_LENGTH                              ; Move to next task
        .IF (esi >= ds:[_TASK_SYSTEM_NEXT_OFFSET])
            mov     esi,_FIRST_TASK_ENTRY                           ; If this line executes, we're past the end so we start over
        .ENDIF

      ; See if this one meets our criteria
        cmp     word ptr ds:[esi+_TASK_ENTRY_HANDLE],-1             ; Handle has to be valid
        jz      next_one
        cmp     byte ptr ds:[esi+_TASK_ENTRY_MODE],_LINEAR          ; And it must be a linear mode task to get a timeslice
        jz      found_match
        cmp     byte ptr ds:[esi+_TASK_ENTRY_MODE],_SLAVE + _LINEAR
        jnz     next_one

      found_match:
      ; We found our task
        mov     bl,byte ptr ds:[esi+_TASK_ENTRY_TICKS]              ; If here, then this is the next task
        mov     byte ptr ds:[esi+_TASK_ENTRY_TICKS_LEFT],bl
        jmp     exec_task_switch
      ; If we're here, then no tasks are needing cpu time (they're all waiting for input or suspended)
      ; This is idle time, so let's check if any tasks use idle processing

      next_one:
        dec     ecx
        jnz     linear_top




      ;;---------------------------
      ;; ⁄ƒƒƒƒƒƒƒƒƒƒƒƒƒø
      ;; ¥ Search IDLE ≥   Here we look for tasks that are valid and marked _IDLE_MODE.
      ;; ¿√√√√√√√√√√√√√Ÿ   We do another top-down search (as above).  Note, the extra
      ;;                   time this will take shouldn't be an issue because we're
      ;;                   currently in idle mode. :)
      ;;
      ;;
        mov     ecx,dword ptr ds:[_TASK_SYSTEM_TOTAL_ENTRIES_BASE_0]
        mov     esi,dword ptr ds:[_TASK_SYSTEM_CURRENT_TASK_OFFSET]
      idle_top:
        add     esi,_TASK_ENTRY_LENGTH
        .IF (esi >= ds:[_TASK_SYSTEM_NEXT_OFFSET])
          ; We're passed the end, start back at the beginning
            mov     esi,_FIRST_TASK_ENTRY
        .ENDIF

      ; See if this one meets our criteria
        cmp     word ptr ds:[esi+_TASK_ENTRY_HANDLE],-1
        jz      next_one2
        cmp     byte ptr ds:[esi+_TASK_ENTRY_MODE],_IDLE
        jnz     next_one2

      found_match2:
      ; We found our task
        mov     bl,byte ptr ds:[esi+_TASK_ENTRY_TICKS]
        mov     byte ptr ds:[esi+_TASK_ENTRY_TICKS_LEFT],bl
        jmp     exec_task_switch

      next_one2:
        dec     ecx
        jnz     idle_top
      ; If we're here, then no tasks need linear or idle cpu time
      ; We revert back to our main Exodus task and wait
        mov     esi,_FIRST_TASK_ENTRY




      ;;---------------------------
      ;; ⁄ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒø
      ;; ¥ Execute task switch ≥    The task switch takes place to whatever task
      ;; ¿√√√√√√√√√√√√√√√√√√√√√Ÿ    is currently specified.  It can be the calling
      ;;                            task if only one task is currently active in
      ;;                            linear mode.  That's all defined in the logic
      ;;                            above.  Regardless, a task switch will occur.
      ;;
    exec_task_switch:
      ;; Modify the back-link to point to the correct task
        mov     bx,word ptr ds:[esi+_TASK_ENTRY_GDT_TSS]
        mov     dx,word ptr ds:[_TASK_SYSTEM_CURRENT_TASK_TSS]
        .IF (dx != bx)
          ; We're going to a separate task

          ; Save the current FPU (if it needs saving)
            mov     edi,dword ptr ds:[_TASK_SYSTEM_CURRENT_TASK_OFFSET]
            .IF (byte ptr ds:[edi+_TASK_ENTRY_USES_FPU] != 0)
              ; This task uses the FPU
                mov     ebx,dword ptr ds:[edi+_TASK_ENTRY_TSS_LINEAR_OFFSET]
                fsave   gs:[ebx+_TSS_FPU_SAVE_AREA]
            .ENDIF

          ; Update the header info
            mov     word ptr ds:[_TASK_SYSTEM_CURRENT_TASK_TSS],bx
            mov     word ptr gs:[_sTASK_SWITCH_TSS+_TSS_BACK_LINK],bx
            mov     dword ptr ds:[_TASK_SYSTEM_CURRENT_TASK_OFFSET],esi

          ; Restore the new FPU (if it needs restoring)
            .IF (byte ptr ds:[esi+_TASK_ENTRY_USES_FPU] != 0)
                mov     ebx,dword ptr ds:[esi+_TASK_ENTRY_TSS_LINEAR_OFFSET]
                frstor  gs:[ebx+_TSS_FPU_SAVE_AREA]
            .ENDIF
        .ENDIF
        iretd




      ;;---------------------------
      ;; ⁄ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒø
      ;; ¥ After task switch ≥  After the task switch, the CS:EIP value stored
      ;; ¿√√√√√√√√√√√√√√√√√√√Ÿ  in the _sTASK_SYSTEM_TSS will be the one immediately
      ;;                        after the IRETD above.  So, to compensate for that
      ;;                        fact we add the following JMP to go back up.
      ;;
        jmp     task_switch_start
    invTASK_switch_task     ENDP
