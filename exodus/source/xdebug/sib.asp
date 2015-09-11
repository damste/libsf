            .IF (ah == 10b)
                ; It's an indirect memory operand with a 16/32-bit displacement
                add     bx,5
                mov     dl,byte ptr [si+bx-5]
                mov     CS:sib_byte,dl
                mov     edx,dword ptr [si+bx-4]
                mov     dword ptr CS:temp_buffer[0],edx
                call    display_instruction
                call    display_segment_override
                call    display_open_bracket
                mov     ah,al
                and     al,0111b
                call    display_register_name_indirect_sib
                call    display_plus_sign
                mov     edx,dword ptr CS:temp_buffer[0]
                call    show_register_adr_size_override_no_color
                call    display_close_bracket
                call    display_comma
                mov     al,ah
                shr     al,3
                and     al,0111b
                call    display_register_name_op_size_override
            .ELSEIF (ah == 01b)
              ; It's an indirect memory operand with an 8-bit displacement
                inc     bx
                mov     dl,byte ptr [si+bx-1]
                mov     byte ptr CS:temp_buffer[0],dl
                call    display_instruction
                call    display_segment_override
                call    display_open_bracket
                mov     ah,al
                and     al,0111b
                call    display_register_name_indirect_sib
                call    display_plus_sign
                mov     edx,dword ptr CS:temp_buffer[0]
                call    show_register_adr_size_override_no_color
                call    display_close_bracket
                call    display_comma
                mov     al,ah
                shr     al,3
                and     al,0111b
                call    display_register_name_op_size_override
            .ELSE
              ; It is 00b, which means it's either direct memory operand or a based, indexed or based & indexed operand
                mov     ah,al
                and     ah,0111b
                .IF (ah == 110b)
                  ; It's a direct memory operand
                    add     bl,2
                    call    display_instruction
                    call    display_segment_override
                .ELSE
                  ; It's a based, indexed or based & indexed operand
                    call    display_instruction
                    call    display_segment_override
                .ENDIF
            .ENDIF