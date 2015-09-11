@echo off
if "%1"=="1" goto ed1
if "%1"=="2" goto ed2
if "%1"=="3" goto ed3
if "%1"=="4" goto ed4
if "%1"=="5" goto ed5
if "%1"=="6" goto ed6
if "%1"=="7" goto ed7
if "%1"=="8" goto ed8
if "%1"=="9" goto ed9
if "%1"=="10" goto ed10
if "%1"=="e" goto ed_e
if "%1"=="E" goto ed_e
if "%1"=="c" goto ed_c
if "%1"=="C" goto ed_c
if "%1"=="d" goto ed_d
if "%1"=="D" goto ed_d
if "%1"=="11" goto ed11
if "%1"=="31" goto ed31
if "%1"=="32" goto ed32
if "%1"=="33" goto ed33
if "%1"=="34" goto ed34
if "%1"=="35" goto ed35
if "%1"=="36" goto ed36
if "%1"=="37" goto ed37
if "%1"=="38" goto ed38
if "%1"=="39" goto ed39
if "%1"=="41" goto ed41
if "%1"=="42" goto ed42
if "%1"=="43" goto ed43
if "%1"=="44" goto ed44
if "%1"=="45" goto ed45
if "%1"=="46" goto ed46
if "%1"=="47" goto ed47
if "%1"=="51" goto ed51
if "%1"=="52" goto ed52
if "%1"=="53" goto ed53
if "%1"=="81" goto ed81
if "%1"=="82" goto ed82
if "%1"=="83" goto ed83
if "%1"=="84" goto ed84
if "%1"=="85" goto ed85
if "%1"=="86" goto ed86
if "%1"=="91" goto ed91
if "%1"=="92" goto ed92
if "%1"=="93" goto ed93
if "%1"=="94" goto ed94
if "%1"=="e1" goto ed_e1
if "%1"=="d1" goto ed_d1
call eq
goto quit

:ed1
e pb\pb.c
goto quit

:ed11
e pb\extras.c
goto quit

:ed2
e boot\boot.asm
goto quit

:ed3
e bootup\bootup.asm
goto quit

:ed4
e debi\debi.asm
goto quit

:ed5
e vga\vga.asm
goto quit

:ed6
e kbd\kbd.asm
goto quit

:ed7
e mouse\mouseps2.asm
goto quit

:ed8
e bios\bios.asm
goto quit

:ed9
e x86\x86.asm
goto quit

:ed10
e disk\disk.asm
goto quit

:ed_c
e cv\cv.asm
goto quit

:ed_d
e dsw\dsw.c
goto quit

:ed_e
e exodus\exodus.asm
goto quit

:ed31
e common\equates.asp
goto quit

:ed32
e bootup\init16.asp
goto quit

:ed33
e bootup\init32.asp
goto quit

:ed34
e common\errors.asp
goto quit

:ed35
e bootup\data16.asp
goto quit

:ed36
e bootup\data32.asp
goto quit

:ed37
e bootup\native.asp
goto quit

:ed38
e bootup\req.asp
goto quit

:ed39
e bootup\ini.asp
goto quit

:ed41
e debi\debidata.asp
goto quit

:ed42
e debi\debi_eq.asp
goto quit

:ed43
e debi\debi_mac.asp
goto quit

:ed44
e debi\debilogo.asp
goto quit

:ed45
e debi\cfsca.asp
goto quit

:ed46
e debi\todo.asp
goto quit

:ed47
e debi\disk.asp
goto quit

:ed51
e vga\vga.asp
goto quit

:ed52
e vga\mono.asp
goto quit

:ed53
e vga\global.asp
goto quit

:ed81
e bios\timer.asp
goto quit

:ed82
e bios\tasks.asp
goto quit

:ed83
e bios\objects.asp
goto quit

:ed84
e bios\create.asp
goto quit

:ed85
e bios\redraw.asp
goto quit

:ed86
e bios\mouse.asp
goto quit

:ed91
e x86\asm.asp
goto quit

:ed92
e x86\asm_data.asp
goto quit

:ed93
e x86\disasm.asp
goto quit

:ed94
e x86\dis_data.asp
goto quit

:ed_e1
e exodus\ex_data.asp
goto quit

:ed_d1
e dsw\extras.c
goto quit

:quit
