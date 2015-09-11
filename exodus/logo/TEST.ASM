; test.asm

TITLE test

    .DOSSEG

    .MODEL tiny

    .486P

    .STACK 0h

    .DATA
INCLUDE \assembly\c_macros.asp
INCLUDE \assembly\keylist.asp

RAMDAC_INDEX_READ       EQU 3c7h
RAMDAC_INDEX_WRITE      EQU 3c8h
RAMDAC_DATA             EQU 3c9h

    .CODE
    .STARTUP
    mov     ax,cs
    mov     ds,ax
    mov     es,ax

  ; Enter graphics mode
    mov     ax,13h
    int     10h

  ; Open file
    mov     dx,offset filename
    @ReadOnly
    @OpenFile
    mov     file_handle,ax

  ; Seek to a particular offset
    mov     bx,ax
    xor     cx,cx
    mov     dx,1078
    @SeekSet
    @DOS

  ; Read the file
    mov     bx,file_handle
    mov     dx,offset file_load_area
    mov     cx,64000
    @ReadFile

  ; Copy to the buffer from the load area to video memory
    mov     ax,0a000h
    mov     es,ax
    xor     di,di
    mov     si,offset file_load_area + 64000
    mov     cx,200
    .REPEAT
        push    cx
        sub     si,320
        push    si

        mov     cx,320
        .REPEAT
            mov     al,byte ptr ds:[si]
            inc     si
            mov     byte ptr es:[di],al
            inc     di
        .UNTILCXZ

        pop     si
        pop     cx
    .UNTILCXZ

  ; Update the palette to reflect the one on disk
    mov     bx,file_handle
    xor     cx,cx
    mov     dx,54
    @SeekSet
    @DOS

  ; Read the palette data
    mov     bx,file_handle
    mov     cx,4*256
    mov     dx,offset file_load_area
    @ReadFile

  ; Now, set the palette
    mov     si,offset file_load_area
    mov     cx,256
    mov     dx,RAMDAC_INDEX_WRITE
    xor     al,al
    out     dx,al
    mov     dx,RAMDAC_DATA
    .REPEAT
        mov     al,byte ptr [si+2]                                  ; Red
        shr     al,2
        out     dx,al

        mov     al,byte ptr [si+1]                                  ; Green
        shr     al,2
        out     dx,al

        mov     al,byte ptr [si]                                    ; Blue
        shr     al,2
        out     dx,al

        add     si,4
        inc     bl
    .UNTILCXZ

  ; Wait for a key
  @@:
;    mov     dx,0500h
;    mov     ah,02h
;    int     10h
;
;    xor     edx,edx
;    mov     dl,adjust_palette
;    mov     ebx,16
;    call    display_radix_in_edx
;
;    mov     dx,offset semicolon_space
;    mov     ah,09h
;    int     21h
;
;    mov     al,current_modify
;    .IF (al == 0)
;        mov     dx,offset red_text
;    .ELSEIF (al == 1)
;        mov     dx,offset green_text
;    .ELSE
;        mov     dx,offset blue_text
;    .ENDIF
;    mov     ah,09h
;    int     21h
;
;    mov     dx,offset several_spaces
;    mov     ah,09h
;    int     21h

    xor     ah,ah
    int     16h
    .IF (ax == up || ax == grey_up)
      ; They want to go to the next palette
        inc     adjust_palette
        call    read_palette
    .ELSEIF (ax == down || ax == grey_down)
      ; They want to go to the previous palette
        dec     adjust_palette
        call    read_palette
    .ELSEIF (ax == left || ax == grey_left)
      ; They want to move to the next part of the color
        .IF (current_modify > 0)
            dec     current_modify
        .ENDIF
    .ELSEIF (ax == right || ax == grey_right)
      ; They want to move to the previous part of the color
        .IF (current_modify < 2)
            inc     current_modify
        .ENDIF
    .ELSEIF (al == '+' || ax == pgup || ax == grey_pgup)
      ; They want to increase this part of the palette
        mov     al,current_modify
        .IF (al == 0)
          ; Red
            inc     red
        .ELSEIF (al == 1)
          ; Green
            inc     green
        .ELSE
          ; Blue
            inc     blue
        .ENDIF
        call    write_palette
    .ELSEIF (al == '-' || ax == pgdn || ax == grey_pgdn)
      ; They want to decrease this part of the palette
        mov     al,current_modify
        .IF (al == 0)
          ; Red
            dec     red
        .ELSEIF (al == 1)
          ; Green
            dec     green
        .ELSE
          ; Blue
            dec     blue
        .ENDIF
        call    write_palette
    .ELSEIF (ax == escape)
      ; They're done
        jmp     @F
    .ELSEIF (al == 'w' || al == 'W')
      ; They want to write the formatted structure
      ; Adjust all the data items on screen (so all of the values are at the head of the palette
      ; Initialize our array
        mov     si,offset file_load_area
        mov     cx,256
        xor     al,al
        .REPEAT
            mov     byte ptr [si],al
            mov     byte ptr [si+1],0
            inc     al
            add     si,2
        .UNTILCXZ
      ; Now, analyze the screen and find out which colors we presently have
        mov     ax,0a000h
        mov     es,ax
        xor     di,di
        mov     si,offset file_load_area
        mov     cx,320*200
        .REPEAT
            xor     bx,bx
            mov     bl,byte ptr es:[di]
            shl     bx,1
            mov     byte ptr ds:[si+bx+1],1
            inc     di
        .UNTILCXZ

      ; Now, modify those values so they equate to the first portions of the data stream
        mov     si,offset file_load_area
        mov     cx,256
        mov     al,1
        .REPEAT
            .IF (byte ptr [si+1] != 0)
              ; This is a color
.IF (byte ptr [si] == 0d3h)
    int 3
.ENDIF
                mov     byte ptr [si+1],al
                inc     al
            .ENDIF
            add     si,2
        .UNTILCXZ
        mov     cs:palette_count,al

      ; Now, adjust them on screen
        xor     di,di
        mov     si,offset file_load_area
        mov     cx,320*200
        .REPEAT
            xor     bx,bx
            mov     bl,byte ptr es:[di]
            shl     bx,1
            mov     dl,byte ptr ds:[si+bx+1]
            mov     byte ptr es:[di],dl
            inc     di
        .UNTILCXZ

      ; Now, adjust the palette
        mov     si,offset file_load_area
        mov     cx,256
        xor     al,al
        .REPEAT
            .IF (byte ptr [si+1] != 0)
                mov     al,byte ptr [si]
                mov     adjust_palette,al
                call    read_palette
                mov     al,byte ptr [si+1]
                mov     adjust_palette,al
                call    write_palette
            .ENDIF
            add     si,2
        .UNTILCXZ

      ; Create the output file
        mov     dx,offset out_filename
        @NoAttributes
        @CreateFile
        mov     out_file_handle,ax

      ; Write the palette
        mov     si,offset file_load_area
        xor     cx,cx
        mov     cl,palette_count
        mov     byte ptr [si],cl
        inc     si
        xor     al,al
        .REPEAT
            mov     adjust_palette,al
            call    read_palette
            mov     dl,red
            mov     byte ptr [si],dl
            mov     dl,green
            mov     byte ptr [si+1],dl
            mov     dl,blue
            mov     byte ptr [si+2],dl
            add     si,3
            inc     al
        .UNTILCXZ

        mov     dx,offset file_load_area
        xor     cx,cx
        mov     cl,palette_count
        mov     bx,cx
        shl     cx,1
        add     cx,bx
        inc     cx
        mov     bx,out_file_handle
        @WriteFile


        mov     ax,0a000h
        mov     ds,ax
        xor     si,si
        push    cs
        pop     es
        mov     di,offset file_load_area
        mov     cx,320*200
        .WHILE (cx > 0)
            mov     al,byte ptr [si]
            mov     dl,1
            .WHILE (byte ptr [si+1] == al && dl <= 0feh && cx > 1)
                inc     dl
                inc     si
                dec     cx
            .ENDW
            mov     byte ptr es:[di],dl
            mov     byte ptr es:[di+1],al
            add     di,2
            inc     si
            dec     cx
        .ENDW
        mov     cx,di
        sub     cx,offset file_load_area
        push    cs
        pop     ds
        mov     dx,offset file_load_area
        mov     bx,out_file_handle
        @WriteFile
        xor     ah,ah
        int     16h
        jmp     @F
    .ENDIF
    jmp     @B


  ; Re-enter text mode
  @@:
    mov     ax,03h
    int     10h

    .EXIT


read_palette    PROC
    push    dx
    push    ax

    mov     dx,RAMDAC_INDEX_READ
    mov     al,adjust_palette
    out     dx,al
    mov     dx,RAMDAC_DATA
    in      al,dx
    mov     red,al
    in      al,dx
    mov     green,al
    in      al,dx
    mov     blue,al

    pop     ax
    pop     dx
    ret
read_palette    ENDP


write_palette    PROC
    push    dx
    push    ax

    mov     dx,RAMDAC_INDEX_WRITE
    mov     al,adjust_palette
    out     dx,al
    mov     dx,RAMDAC_DATA
    mov     al,red
    out     dx,al
    mov     al,green
    out     dx,al
    mov     al,blue
    out     dx,al

    pop     ax
    pop     dx
    ret
write_palette    ENDP


display_radix_in_edx    PROC
    pushad
    push    ds
    sub     esp,16                                                  ; Assume a maximum length of 12 chars (4 extra for boundary)
    mov     ebp,esp

    call    generate_radix_string
    mov     dx,si
    mov     ah,09h
    int     21h

    add     esp,16
    pop     ds
    popad
    ret
display_radix_in_edx    ENDP


generate_radix_string   PROC
    mov     byte ptr [ebp+12],'$'                               ; Terminate the string we're building
    mov     esi,ebp
    add     esi,11
    mov     eax,edx
    and     ebx,0ffffh
  @@:
    xor     edx,edx
    div     ebx
    .IF (dl > 9)
        add     dl,'a'-10                                       ; Make it a letter if it's above 9 (10+ cannot be represented in 1 digit)
    .ELSE
        add     dl,'0'                                          ; Make it a number
    .ENDIF
    mov     byte ptr ss:[esi],dl
    dec     esi                                                 ; Decrement (move to next position to store data)
    cmp     esi,ebp
    jz      @F
    cmp     eax,0
    jnz     @B
  @@:
    push    ss
    pop     ds
    inc     esi                                                 ; Add back for the one we decremented above
  ; Right now, ds:[esi] - pointer to the value to display
    ret
generate_radix_string   ENDP



filename        db  "boot_scr.bmp",0
file_handle     dw  0

out_filename    db  "file.raw",0
out_file_handle dw  0

semicolon_space db  "; $"
several_spaces  db  5 dup(32),"$"

red_text        db  "red$"
green_text      db  "green$"
blue_text       db  "blue$"

palette_count   db  0
adjust_palette  db  0
current_modify  db  0
red             db  0
green           db  0
blue            db  0

file_load_area  db  64000 dup(0)

END