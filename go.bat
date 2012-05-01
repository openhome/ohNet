@echo off

rem    Invoke developer tools.
rem    Invoke without arguments to get a list of available tools.
rem    Requires the ohdevtools to be available locally. Set
rem    OHDEVTOOLS_ROOT to their directory if this script cannot
rem    find them.

setlocal
set PROJECT_ROOT=%~dp0
cd %PROJECT_ROOT%

rem Force Python processes to be unbuffered. Prevents jumbled
rem output during CI builds due to buffering on stdout.
set PYTHONUNBUFFERED=x

call :fallback_devtools "%PROJECT_ROOT%\ohdevtools"
call :fallback_devtools "%PROJECT_ROOT%\..\ohdevtools"

if not exist "%OHDEVTOOLS_ROOT%" (
   echo OHDEVTOOLS_ROOT not set.
   echo Tried looking in %OHDEVTOOLS_ROOT%.
   echo Please set OHDEVTOOLS_ROOT to point to the location of the ohdevtools scripts.
   exit /b 1
)

if defined PYTHONPATH (
    set PYTHONPATH=%OHDEVTOOLS_ROOT%;%PYTHONPATH%
) else (
    set PYTHONPATH=%OHDEVTOOLS_ROOT%
)

:run
python -u -m go %*
goto :eof

:fallback_devtools
rem    If OHDEVTOOLS_ROOT doesn't point to an existing directory,
rem    point it towards the provided directory converted to an
rem    absolute path.
if defined OHDEVTOOLS_ROOT (
  if exist "%OHDEVTOOLS_ROOT%" (
    exit /b 0
  )
)
set OHDEVTOOLS_ROOT=%~f1
exit /b 0
