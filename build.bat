@ECHO off
SETLOCAL ENABLEDELAYEDEXPANSION

IF NOT EXIST build MKDIR build


IF "%1" == "repl" GOTO repl


:repl
    IF NOT EXIST build\repl MKDIR build\repl

    SET MACROS=/DGUTTURAL_DEBUG
    SET COMPILER_FLAGS=/nologo /EHsc /Od /W4 /wd4127 /wd4996 /Zi /Fobuild\repl\ /Fdbuild\repl\ /c /I "include"

    FOR /r source %%f IN ("*.cpp") DO cl %COMPILER_FLAGS% "%%f" %MACROS%

    cl %COMPILER_FLAGS% target\repl.cpp %MACROS%

    PUSHD build\repl

    SET LINKER_FLAGS=/NOLOGO /DEBUG

    link %LINKER_FLAGS% /OUT:guttural.exe *.obj

    POPD

    GOTO end

:end
    ECHO "Finished"
