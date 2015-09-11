@echo off
if "%1"=="all" goto goall
if "%1"=="1" goto go1
if "%1"=="2" goto go2
if "%1"=="3" goto go3
if "%1"=="4" goto go4
if "%1"=="5" goto go5
if "%1"=="6" goto go6
if "%1"=="7" goto go7
if "%1"=="8" goto go8
if "%1"=="9" goto go9
if "%1"=="10" goto go10
if "%1"=="e" goto go_e
if "%1"=="E" goto go_e
if "%1"=="c" goto go_c
if "%1"=="C" goto go_c
if "%1"=="d" goto go_d
if "%1"=="D" goto go_d
echo �
echo Usage:  go #  ; where # is 1-10 or E
echo �
echo �  1 - *pb
echo �  2 - boot
echo �  3 - bootup
echo �  4 - debi
echo �  5 - vga
echo �  6 - keyboard
echo �  7 - mouse ps/2
echo �  8 - bios
echo �  9 - x86 disassembler
echo � 10 - disk
echo �  c - CodeView
echo �  e - exodus.com
echo �  d - *Debi Source Writer
echo �
goto quit

:goall
call go 2
call go 3
call go 4
call go 5
call go 6
call go 7
call go 8
call go 9
call go 10
call go c
call go e
goto quit

:go1
cl /G2 /Od /Zi /AT /FPi87 /F 4000 pb\pb.c
if errorlevel==1 goto errors
goto quit

:go2
ml /Sn /Fl /Sa /Fm /FR %2 %3 %4 boot\boot.asm
if errorlevel==1 goto errors
REM bscmakev /r boot.sbr
erase boot.obj
erase boot.sbr
move boot.com .\exec\boot.bin < \exodus\yes.txt
move boot.lst .\list < \exodus\yes.txt
move boot.bsc .\list < \exodus\yes.txt
move boot.map .\list < \exodus\yes.txt
goto quit

:go3
ml /Sn /Fl /Sa /Fm /FR %2 %3 %4 bootup\bootup.asm
if errorlevel==1 goto errors
REM bscmakev /r bootup.sbr
erase bootup.obj
erase bootup.sbr
move bootup.com .\exec\bootup.bin < \exodus\yes.txt
move bootup.lst .\list < \exodus\yes.txt
move bootup.bsc .\list < \exodus\yes.txt
move bootup.map .\list < \exodus\yes.txt
goto quit

:go4
ml /Sn /Fl /Sa /Fm /FR %2 %3 %4 debi\debi.asm
if errorlevel==1 goto errors
REM bscmakev /r debi.sbr
erase debi.obj
erase debi.sbr
move debi.com .\exec\debi.drv < \exodus\yes.txt
move debi.lst .\list < \exodus\yes.txt
move debi.bsc .\list < \exodus\yes.txt
move debi.map .\list < \exodus\yes.txt
goto quit

:go5
ml /Sn /Fl /Sa /Fm /FR %2 %3 %4 vga\vga.asm
if errorlevel==1 goto errors
REM bscmakev /r vga.sbr
erase vga.obj
erase vga.sbr
move vga.com .\exec\vga.drv < \exodus\yes.txt
move vga.lst .\list < \exodus\yes.txt
move vga.bsc .\list < \exodus\yes.txt
move vga.map .\list < \exodus\yes.txt
goto quit

:go6
ml /Sn /Fl /Sa /Fm /FR %2 %3 %4 kbd\kbd.asm
if errorlevel==1 goto errors
REM bscmakev /r kbd.sbr
erase kbd.obj
erase kbd.sbr
move kbd.com .\exec\kbd.drv < \exodus\yes.txt
move kbd.lst .\list < \exodus\yes.txt
move kbd.bsc .\list < \exodus\yes.txt
move kbd.map .\list < \exodus\yes.txt
goto quit

:go7
ml /Sn /Fl /Sa /Fm /FR %2 %3 %4 mouse\mouseps2.asm
if errorlevel==1 goto errors
REM bscmakev /r mouseps2.sbr
erase mouseps2.obj
erase mouseps2.sbr
move mouseps2.com .\exec\mouseps2.drv < \exodus\yes.txt
move mouseps2.lst .\list < \exodus\yes.txt
move mouseps2.bsc .\list < \exodus\yes.txt
move mouseps2.map .\list < \exodus\yes.txt
goto quit

:go8
ml /Sn /Fl /Sa /Fm /FR %2 %3 %4 bios\bios.asm
if errorlevel==1 goto errors
REM bscmakev /r bios.sbr
erase bios.obj
erase bios.sbr
move bios.com .\exec\bios.drv < \exodus\yes.txt
move bios.lst .\list < \exodus\yes.txt
move bios.bsc .\list < \exodus\yes.txt
move bios.map .\list < \exodus\yes.txt
goto quit

:go9
ml /Sn /Fl /Sa /Fm /FR %2 %3 %4 x86\x86.asm
if errorlevel==1 goto errors
REM bscmakev /r x86.sbr
erase x86.obj
erase x86.sbr
move x86.com .\exec\x86.drv < \exodus\yes.txt
move x86.lst .\list < \exodus\yes.txt
move x86.bsc .\list < \exodus\yes.txt
move x86.map .\list < \exodus\yes.txt
goto quit

:go10
ml /Sn /Fl /Sa /Fm /FR %2 %3 %4 disk\disk.asm
if errorlevel==1 goto errors
REM bscmakev /r disk.sbr
erase disk.obj
erase disk.sbr
move disk.com .\exec\disk.drv < \exodus\yes.txt
move disk.lst .\list < \exodus\yes.txt
move disk.bsc .\list < \exodus\yes.txt
move disk.map .\list < \exodus\yes.txt
goto quit

:go_d
cl /G2 /Od /Zi /Gs /AT /FPi87 /F 4000 dsw\dsw.c
if errorlevel==1 goto errors
goto quit

:go_c
ml /Sn /Fl /Sa /Fm /FR %2 %3 %4 cv\cv.asm
REM bscmakev /r cv.sbr
erase cv.obj
erase cv.sbr
move cv.com .\exec\cv.drv < \exodus\yes.txt
move cv.lst .\list < \exodus\yes.txt
move cv.bsc .\list < \exodus\yes.txt
move cv.map .\list < \exodus\yes.txt
goto quit

:go_e
ml /Sn /Fl /Sa /Fm /FR %2 %3 %4 exodus\exodus.asm
if errorlevel==1 goto errors
REM bscmakev /r exodus.sbr
erase exodus.obj
erase exodus.sbr
move exodus.com .\exec\exodus.drv < \exodus\yes.txt
move exodus.lst .\list < \exodus\yes.txt
move exodus.bsc .\list < \exodus\yes.txt
move exodus.map .\list < \exodus\yes.txt
goto quit

:errors
echo Errors!

:quit
