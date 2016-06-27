@echo off

REM remove common files
del /s command.vjr
del /s screen.vjr
del /s system.log
del /s *.exe
del /s *.obj
del /s *.ilk
del /s *.pdb
del /s *.idb
del /s *.plg
del /s *.ncb
del /s *.sdf
del /s vjr.aps
del /s *.filters
del /s UpgradeLog.htm

echo Removing compiler folders
for /d /r . %%d in (Debug Release .clang .codelite ipch x64 .vs) do @if exist "%%d" echo "%%d" && rd /s/q "%%d"
REM All done

pause
