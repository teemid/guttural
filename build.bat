@ECHO off
SETLOCAL ENABLEDELAYEDEXPANSION

IF NOT EXIST build mkdir build

IF "%1" == "repl" GOTO repl

:repl
    SET MACROS=/DGUTTURAL_DEBUG
    SET COMPILER_FLAGS=/nologo /Od /W4 /wd4127 /wd4996 /Zi /Fobuild\ /Fobuild\ /c /I "include" /EHsc

    FOR /r %%f  IN ("source\*.cpp") DO cl %COMPILER_FLAGS% "%%f" %MACROS%

    PUSHD build

    SET LINKER_FLAGS=/NOLOGO /DEBUG

    link %LINKER_FLAGS% /OUT:guttural.exe *.obj

    POPD

    GOTO end

:end
    ECHO "Finished"
