; macros.asp
;
; Exodus macros, used various places
;



callfp     MACRO   _seg:REQ, _offset:REQ
; This macro:   callfp  _code_seg, _offset
;
    db  9ah
    dd  _offset
    dw  _seg
ENDM




callg      MACRO   _seg:REQ
; This macro:   callg   _call_gate
    db  9ah
    dd  0
    dw  _seg
ENDM




jmpg       MACRO   _seg:REQ
; This macro:   jmpg    _call_gate
    db  0eah
    dd  0
    dw  _seg
ENDM




callf      MACRO   _func:REQ
; This macro:   callf   function_name
    push    cs
    call    _func
ENDM




@IO_pause   MACRO
    jmp     $+2
ENDM