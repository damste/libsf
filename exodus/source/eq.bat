@echo off
echo .
echo ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿                             ÚÄÄÄÄÄÄÄÄÄÄÄÄ¿
echo ³ Exodus Programming ³                             ³ BOOTUP.COM ³
echo ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ                             ÀÄÄÄÄÄÄÄÄÄÄÄÄÙ
echo   ed  1 - pb.c             ; pb.exe                  ed 31 - bootup\equates.asp    ; Constants
echo   ed  2 - boot.asm         ; boot.com                ed 32 - bootup\init16.asp     ; 16-bit Initialization routines
echo   ed  3 - bootup.asm       ; bootup.com              ed 33 - bootup\init32.asp     ; 32-bit Initialization routines
echo   ed  4 - debi.asm         ; debi.drv                ed 34 - bootup\errors.asp     ; Error codes
echo   ed  5 - vga.asm          ; vga.drv                 ed 35 - bootup\data16.asp     ; Data used by 16-bit init code
echo   ed  6 - keyboard.asm     ; keyboard.drv            ed 36 - bootup\data32.asp     ; Data used by 32-bit code
echo   ed  7 - mouse_ps2.asm    ; mouse_ps2.drv           ed 37 - bootup\native.asp     ; Native primative declarations
echo   ed  8 - bios.asm         ; bios.drv                ed 38 - bootup\req.asp        ; requestor()
echo   ed  9 - x86.asm          ; x86.drv                 ed 39 - bootup\ini.asp        ; EXODUS.INI parser
echo   ed 10 - disk.asm         ; disk.drv
echo   ed  e - exodus.asm       ; exodus.com
echo   ed  d - dsw.c            ; dsw.com
echo .
echo ÚÄÄÄÄÄÄÄÄÄÄ¿                   ÚÄÄÄÄÄÄÄÄÄ¿
echo ³ DEBI.DRV ³                   ³ VGA.DRV ³
echo ÀÄÄÄÄÄÄÄÄÄÄÙ                   ÀÄÄÄÄÄÄÄÄÄÙ
echo   ed 41 - debi\debidata.asp      ed 51 - vga\vga.asp
echo   ed 42 - debi\debi_eq.asp       ed 52 - vga\mono.asp
echo   ed 43 - debi\debi_mac.asp      ed 53 - vga\global.asp
echo   ed 44 - debi\debilogo.asp
echo   ed 45 - debi\cfsca.asp
echo   ed 46 - debi\todo.asp
echo   ed 47 - debi\disk.asp
echo .
echo ÚÄÄÄÄÄÄÄÄÄÄ¿                   ÚÄÄÄÄÄÄÄÄÄ¿
echo ³ BIOS.DRV ³                   ³ X86.DRV ³
echo ÀÄÄÄÄÄÄÄÄÄÄÙ                   ÀÄÄÄÄÄÄÄÄÄÙ
echo   ed 81 - bios\timer.asp         ed 91 - x86\asm.asp
echo   ed 82 - bios\tasks.asp         ed 92 - x86\asm_data.asp
echo   ed 83 - bios\objects.asp       ed 93 - x86\disasm.asp
echo   ed 84 - bios\create.asp        ed 94 - x86\dis_data.asp
echo   ed 85 - bios\redraw.asp
echo   ed 86 - bios\mouse.asp
echo .
echo ÚÄÄÄÄÄÄÄÄÄÄÄÄ¿                 ÚÄÄÄÄÄÄÄÄÄ¿
echo ³ EXODUS.COM ³                 ³ DSW.COM ³
echo ÀÄÄÄÄÄÄÄÄÄÄÄÄÙ                 ÀÄÄÄÄÄÄÄÄÄÙ
echo   ed e1 - exodus\ex_data.asp     ed d1 - dsw\extras.c
echo .
