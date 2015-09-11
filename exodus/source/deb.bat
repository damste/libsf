@echo off
if "%1"=="d" goto deb_d
if "%1"=="D" goto deb_d
if "%1"=="p" goto deb_p
if "%1"=="P" goto deb_p
echo ÿ
echo Options:   p - PB
echo            d - DSW
echo ÿ
goto quit

:deb_p
cv /50 pb.com
goto quit

:deb_d
cv /2 dsw.com
goto quit

:quit
