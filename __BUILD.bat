@echo off
chcp 65001 >nul
title Build Unreal Project

echo ========================================================
echo     Build Unreal Engine project
echo ========================================================
echo.

:: ----- 1. Находим .uproject в текущей папке -----
set UPROJECT_FILE=
for %%f in ("%~dp0*.uproject") do set UPROJECT_FILE=%%f
if not defined UPROJECT_FILE (
    echo [ERROR] No .uproject file found in folder %~dp0
    pause
    exit /b 1
)
echo [1] Project: %UPROJECT_FILE%

:: ----- 2. Определяем имя цели (обычно ИмяПроектаEditor) -----
for %%I in ("%UPROJECT_FILE%") do set PROJECT_NAME=%%~nI
if not defined PROJECT_NAME (
    echo [ERROR] Could not extract project name from %UPROJECT_FILE%
    pause
    exit /b 1
)
set TARGET_NAME=%PROJECT_NAME%Editor
echo [2] Target: %TARGET_NAME%

:: ----- 3. Запускаем сборку -----
call "D:\Epic Games\UE_5.7\Engine\Build\BatchFiles\Build.bat" %TARGET_NAME% Win64 Development -Project=%UPROJECT_FILE% -WaitMutex

:: ----- 4. Открываем лог-файл UnrealBuildTool -----
echo [3] Opening log: C:\Users\AndreyWuzHere\AppData\Local\UnrealBuildTool\Log.txt
start "" "C:\Users\AndreyWuzHere\AppData\Local\UnrealBuildTool\Log.txt"

echo.
echo [DONE] Build process completed.
:: pause