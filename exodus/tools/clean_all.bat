@echo off

REM remove common files
del /s *.exe
del /s *.obj
del /s *.ilk
del /s *.pdb
del /s *.idb
del /s *.plg
del /s *.ncb
del /s *.sdf
REM del /s *.suo
del /s vjr.aps

echo Removing compiler folders
for /d /r . %%d in (Debug Release .clang .codelite ipch x64) do @if exist "%%d" echo "%%d" && rd /s/q "%%d"
REM All done

pause