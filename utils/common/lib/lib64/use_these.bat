@echo off
copy freeglut-64.dll ..\freeglut.dll
REM Note: The following is supposed to be named glew32.dll even as it is a 64-bit DLL
copy glew32-64.dll ..\glew32.dll
copy sdl-64.dll ..\sdl.dll
REM Copy for offline builds
REM copy freeglut-64.dll \libsf_offline\source\vjr\bin\64-bit\freeglut.dll
REM copy glew32-64.dll \libsf_offline\source\vjr\bin\64-bit\glew32.dll
REM copy sdl-64.dll \libsf_offline\source\vjr\bin\64-bit\sdl.dll
