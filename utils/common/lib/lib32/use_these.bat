@echo off
REM copy for debugging
copy freeglut-32.* ..\freeglut.*
copy glew32-32.* ..\glew32.*
copy sdl-32.* ..\sdl.*
copy glew32*.lib ..\
copy freeglut*.lib ..\
REM Copy for offline builds
REM copy freeglut-32.dll \libsf_offline\source\vjr\bin\32-bit\freeglut.dll
REM copy glew32-32.dll \libsf_offline\source\vjr\bin\32-bit\glew32.dll
REM copy sdl-32.dll \libsf_offline\source\vjr\bin\32-bit\sdl.dll
