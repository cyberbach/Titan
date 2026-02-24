@echo off
chcp 65001 >nul
title Clean Temporary Project Files

echo ========================================================
echo     Clean temporary files for UE5 project
echo ========================================================
echo.

REM Удаление папок
if exist "Plugins\ShooterCore\Binaries" (
    echo Removing Plugins\ShooterCore\Binaries...
    rmdir /s /q "Plugins\ShooterCore\Binaries"
)

if exist "Plugins\ShooterCore\Intermediate" (
    echo Removing Plugins\ShooterCore\Intermediate...
    rmdir /s /q "Plugins\ShooterCore\Intermediate"
)

if exist "Intermediate" (
    echo Removing Intermediate...
    rmdir /s /q "Intermediate"
)

if exist "DerivedDataCache" (
    echo Removing DerivedDataCache...
    rmdir /s /q "DerivedDataCache"
)

if exist "Binaries" (
    echo Removing Binaries...
    rmdir /s /q "Binaries"
)

REM Удаление .sln файлов
echo Removing .sln files...
del /q *.sln 2>nul

echo.
echo [DONE] Cleanup finished.
pause