; asm.asp
;
; x86 assembly algorithms
;




; Data and macros
;INCLUDE \exodus\source\debi\asm_data.asp
; These are included in disasm.asp




x86_assemble:
; This routine is used to disassemble an instruction
;
; Upon entry:   ds:[esi] - far ptr to instruction string (such as "mov eax,10") terminated with NULL
;               es:[edi] - where to store x86 instruction encoding
;               * It is known that at most 16 bytes will be required for the instruction
;
; Upon exit:    es:[edi] is updated
;
    retf