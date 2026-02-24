@echo off
chcp 65001 >nul
title Pack Code to Text

echo ========================================================
echo     Pack all executable files into one text file
echo ========================================================
echo.

REM ======== НАСТРОЙКИ ========
set "PROJECT_ROOT=D:\Projects\OnTitanGame\Plugins\ShooterCore"
set "OUTPUT_FILE=%~dp0all_code.txt"
REM ============================

if not exist "%PROJECT_ROOT%" (
    echo [ERROR] Project folder not found: "%PROJECT_ROOT%"
    pause
    exit /b 1
)

echo Collecting files from: %PROJECT_ROOT%
echo Output file: %OUTPUT_FILE%
echo Excluding folders: Intermediate, Binaries, DerivedDataCache, Saved, .vs, Build

(
    for /f "delims=" %%i in ('
        dir /s /b "%PROJECT_ROOT%\*.cpp" "%PROJECT_ROOT%\*.h" 2^>nul ^
        ^| findstr /v /i "\\Intermediate\\ \\Binaries\\ \\DerivedDataCache\\ \\Saved\\ \\.vs\\ \\Build\\"
    ') do (
        echo LOCATION: %%i
        echo FILE: %%~nxi
        type "%%i"
        echo.
    )
) > "%OUTPUT_FILE%"

echo.
echo [DONE] File created: "%OUTPUT_FILE%"
pause