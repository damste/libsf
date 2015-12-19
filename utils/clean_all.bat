@echo off
REM VVM
REM cd \libsf\utils\
REM call vvm__clean_all_dll_and_exe.bat

REM SHA-1
cd \libsf\utils\sha1\
call \libsf\utils\sha1__clean.bat

REM F2H
cd \libsf\utils\fsh\
call \libsf\utils\f2h__clean.bat

REM DSF
cd \libsf\utils\dsf\
call \libsf\utils\dsf__clean.bat

REM Remove the exceedingly large canvas test2 include file
erase \libsf\vvm\core\vvmtests\include\vvmt_canvas_test2.h

REM All done
pause
