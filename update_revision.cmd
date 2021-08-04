@ECHO OFF
SETLOCAL
CD /D %~dp0

ECHO #pragma once > ver_revision.h

SET gitexe="git.exe"
IF NOT EXIST %gitexe% set gitexe="c:\Program Files\Git\bin\git.exe"
IF NOT EXIST %gitexe% set gitexe="c:\Program Files\Git\cmd\git.exe"

IF NOT EXIST %gitexe% GOTO END

%gitexe% log -1 --date=format:%%Y.%%m.%%d --pretty=format:"#define VERSION_DATE %%ad%%n" >> ver_revision.h
%gitexe% log -1 --pretty=format:"#define VERSION_HASH %%h%%n" >> ver_revision.h

<nul set /p strTemp=#define VERSION_BRANCH >> ver_revision.h
%gitexe% symbolic-ref --short HEAD >> ver_revision.h
IF %ERRORLEVEL% NEQ 0 (
ECHO LOCAL >> ver_revision.h
)

ECHO #define VERSION_MAJOR 2 >> ver_revision.h
ECHO #define VERSION_MINOR 0 >> ver_revision.h

<nul set /p strTemp=#define VERSION_REVISION >> ver_revision.h
%gitexe% rev-list --count HEAD >> ver_revision.h
IF %ERRORLEVEL% NEQ 0 (
ECHO 0 >> ver_revision.h
)

ECHO #define stringify(a) stringify_(a) >> ver_revision.h
ECHO #define stringify_(a) #a >> ver_revision.h

:END
ENDLOCAL
EXIT /B
