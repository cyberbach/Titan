@echo off
setlocal enabledelayedexpansion
chcp 65001 >nul
title Build Unreal Project

echo ========================================================
echo     Build Unreal Engine project
echo ========================================================
echo.

:: ----- 1. Находим .uproject в папке скрипта -----
set "SCRIPT_DIR=%~dp0"
set UPROJECT_FILE=
for %%f in ("%SCRIPT_DIR%*.uproject") do set "UPROJECT_FILE=%%f"
if not defined UPROJECT_FILE (
    echo [ERROR] No .uproject file found in folder %SCRIPT_DIR%
    pause
    exit /b 1
)
echo [1] Project: %UPROJECT_FILE%

:: ----- 2. Определяем имя цели (ищем в папке Source файл *Editor.Target.cs) -----
set "TARGET_NAME="
set "SOURCE_DIR=%SCRIPT_DIR%Source"
if not exist "%SOURCE_DIR%" (
    echo [ERROR] Source folder not found: %SOURCE_DIR%
    pause
    exit /b 1
)

pushd "%SOURCE_DIR%"
for %%f in (*Editor.Target.cs) do (
    set "TARGET_FILE=%%f"
    :: Удаляем суффикс "Editor.Target.cs", оставляем имя модуля
    set "TARGET_BASE=!TARGET_FILE:Editor.Target.cs=!"
    set "TARGET_NAME=!TARGET_BASE!Editor"
    goto :target_found
)
popd

:target_found
popd
if not defined TARGET_NAME (
    echo [ERROR] Could not find *Editor.Target.cs file in %SOURCE_DIR%
    pause
    exit /b 1
)
echo [2] Target: %TARGET_NAME%

:: ----- 3. Определяем путь к Engine (приоритет: UE 5.7) -----
set "UE_ROOT="
set "BUILD_BAT="

:: 3.1. Проверяем явный путь для UE 5.7 (можно заменить на свой)
set "UE5_7_PATH=D:\Epic Games\UE_5.7"
if exist "%UE5_7_PATH%\Engine\Build\BatchFiles\Build.bat" (
    set "UE_ROOT=%UE5_7_PATH%"
    set "BUILD_BAT=%UE5_7_PATH%\Engine\Build\BatchFiles\Build.bat"
    echo [3] Engine found at explicit path: %UE_ROOT%
    goto :found_engine
)

:: 3.2. Проверяем реестр для UE 5.7
for %%k in (HKLM HKCU) do (
    for /f "tokens=2*" %%a in ('reg query "%%k\SOFTWARE\EpicGames\Unreal Engine\5.7" /v InstallDir 2^>nul ^| findstr /i "InstallDir"') do (
        if not defined UE_ROOT (
            set "TEST_PATH=%%b"
            if exist "!TEST_PATH!\Engine\Build\BatchFiles\Build.bat" (
                set "UE_ROOT=!TEST_PATH!"
                set "BUILD_BAT=!TEST_PATH!\Engine\Build\BatchFiles\Build.bat"
                echo [3] Engine UE 5.7 found via Windows Registry
                goto :found_engine
            )
        )
    )
)

:: 3.3. Ищем в стандартных папках Epic Games, сортируем по убыванию (более новые версии выше)
set "EPATH_FOUND="
for %%d in (D:\ E:\ C:\ "C:\Program Files") do (
    if not defined EPATH_FOUND (
        if exist "%%~dEpic Games" (
            pushd "%%~dEpic Games" 2>nul
            :: Получаем список папок, начинающихся с UE_ или UnrealEngine_, и сортируем по убыванию имени (версии)
            for /f "delims=" %%e in ('dir /b /ad /o-n UE_* UE* UnrealEngine_* 2^>nul') do (
                if not defined EPATH_FOUND (
                    if exist "%%~dEpic Games\%%e\Engine\Build\BatchFiles\Build.bat" (
                        set "EPATH_FOUND=%%~dEpic Games\%%e"
                    )
                )
            )
            popd 2>nul
        )
    )
)

if defined EPATH_FOUND (
    set "UE_ROOT=%EPATH_FOUND%"
    set "BUILD_BAT=%EPATH_FOUND%\Engine\Build\BatchFiles\Build.bat"
    echo [3] Engine found in standard location: %UE_ROOT%
    goto :found_engine
)

:: Движок не найден
echo [ERROR] Unreal Engine 5.7 not found.
echo.
echo Set environment variable UE_PATH to your engine root.
echo Example: set UE_PATH=D:\Epic Games\UE_5.7
echo.
echo Or ensure Unreal Engine 5.7 is installed via Epic Games Launcher.
pause
exit /b 1

:found_engine
echo [4] Build tool: %BUILD_BAT%

:: ----- 4. Запускаем сборку -----
echo [5] Running: "%BUILD_BAT%" %TARGET_NAME% Win64 Development -Project="%UPROJECT_FILE%" -WaitMutex
call "%BUILD_BAT%" %TARGET_NAME% Win64 Development -Project="%UPROJECT_FILE%" -WaitMutex

:: ----- 5. Открываем лог-файл UnrealBuildTool -----
set "UBT_LOG=%LOCALAPPDATA%\UnrealBuildTool\Log.txt"
echo [6] Opening log: %UBT_LOG%
start "" "%UBT_LOG%"

echo.
echo [DONE] Build process completed.
pause