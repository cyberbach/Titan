@echo off
setlocal enabledelayedexpansion

echo ========================================================
echo     Calculate folder sizes
echo ========================================================
echo.

for %%I in ("%CD%") do set "CURRENT_FOLDER=%%~nxI"
set OUT_FILE=%CURRENT_FOLDER%.txt
if exist %OUT_FILE% del %OUT_FILE%

echo Calculating... Please wait.

for /d %%D in (*) do (
    set "folder=%%D"
    set "size=0"
    for /f "usebackq delims=" %%F in (`dir "%%D" /s /a-d /b 2^>nul`) do (
        set /a size += %%~zF 2>nul
    )
    call :formatSize !size! formatted
    echo !folder!	!formatted! >> %OUT_FILE%
)

echo.
echo [READY] Result in %OUT_FILE%
echo.
pause
exit /b

:formatSize
set "bytes=%~1"
if %bytes% geq 1073741824 (
    set /a "gb_int=%bytes% / 1073741824"
    set /a "gb_frac=(%bytes% %% 1073741824) * 100 / 1073741824"
    if !gb_frac! lss 10 set "gb_frac=0!gb_frac!"
    set "%~2=!gb_int!.!gb_frac! ГБ"
) else if %bytes% geq 1048576 (
    set /a "mb_int=%bytes% / 1048576"
    set /a "mb_frac=(%bytes% %% 1048576) * 100 / 1048576"
    if !mb_frac! lss 10 set "mb_frac=0!mb_frac!"
    set "%~2=!mb_int!.!mb_frac! МБ"
) else if %bytes% geq 1024 (
    set /a "kb_int=%bytes% / 1024"
    set /a "kb_frac=(%bytes% %% 1024) * 100 / 1024"
    if !kb_frac! lss 10 set "kb_frac=0!kb_frac!"
    set "%~2=!kb_int!.!kb_frac! КБ"
) else (
    set "%~2=%bytes% Б"
)
exit /b