@echo off
chcp 65001 >nul
title Generate Unreal Engine Project Files

echo ========================================================
echo     Generate Unreal Engine project files
echo ========================================================
echo.

:: ============================================================
::   АВТОМАТИЧЕСКИЙ ПОИСК UnrealVersionSelector.exe
::   Без хардкода, без реестра, только стандартные пути
:: ============================================================

:: ----- 1. Находим .uproject в текущей папке -----
set UPROJECT_FILE=
for %%f in ("%~dp0*.uproject") do set UPROJECT_FILE=%%f
if not defined UPROJECT_FILE (
    echo [ERROR] No .uproject file found in folder %~dp0
    pause
    exit /b 1
)
echo [1] Project: %UPROJECT_FILE%

:: ----- 2. Ищем UnrealVersionSelector.exe -----
set UVS_EXE=

:: Список возможных корней лаунчера
set LAUNCHER_CANDIDATES[0]=C:\Program Files (x86)\Epic Games\Launcher
set LAUNCHER_CANDIDATES[1]=C:\Program Files\Epic Games\Launcher
set LAUNCHER_CANDIDATES[2]=D:\Program Files (x86)\Epic Games\Launcher
set LAUNCHER_CANDIDATES[3]=D:\Program Files\Epic Games\Launcher
set LAUNCHER_CANDIDATES[4]=D:\Epic Games\Launcher
set LAUNCHER_CANDIDATES[5]=E:\Program Files (x86)\Epic Games\Launcher
set LAUNCHER_CANDIDATES[6]=E:\Program Files\Epic Games\Launcher
set LAUNCHER_CANDIDATES[7]=E:\Epic Games\Launcher
set LAUNCHER_CANDIDATES[8]=C:\Epic Games\Launcher
set LAUNCHER_CANDIDATES[9]=D:\Epic Games\Launcher
set LAUNCHER_CANDIDATES[10]=E:\Epic Games\Launcher

set INDEX=0
:Loop
call set CANDIDATE=%%LAUNCHER_CANDIDATES[%INDEX%]%%
if "%CANDIDATE%"=="" goto :NotFound
if exist "%CANDIDATE%\Engine\Binaries\Win64\UnrealVersionSelector.exe" (
    set UVS_EXE="%CANDIDATE%\Engine\Binaries\Win64\UnrealVersionSelector.exe"
    goto :Found
)
set /a INDEX+=1
goto :Loop

:NotFound
echo [ERROR] UnrealVersionSelector.exe not found.
echo          Please make sure Epic Games Launcher is installed.
pause
exit /b 1

:Found
echo [2] Version Selector: %UVS_EXE%

:: ----- 3. Генерация проектных файлов -----
echo.
echo [3] Generating project files...
echo.
%UVS_EXE% /projectfiles "%UPROJECT_FILE%"

if %errorlevel% neq 0 (
    echo.
    echo [ERROR] Generation failed with code %errorlevel%.
    pause
    exit /b %errorlevel%
) else (
    echo.
    echo [DONE] Project files successfully generated.
)

echo.
pause