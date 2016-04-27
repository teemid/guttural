@ECHO off
SETLOCAL ENABLEDELAYEDEXPANSION

SET PROJECT_DIR="%~dp0"
SET SOURCE_FILES="%~dp0guttural\src\*.c"
SET INCLUDE_DIR="%~dp0guttural\include\"


IF NOT EXIST build mkdir build


IF "%1" == "" GOTO end
IF "%1" == "standalone" GOTO standalone
IF "%1" == "msvc" GOTO msvc
IF "%1" == "msvc" GOTO clang

REM Clang:
REM -O0: No optimizations
REM -c: Run preprocessor, parser, LLVM generation, assembler
REM -g: Generate debug information
REM -o: Write output to file
REM -D: Adds an implicit #define into the predefines buffer which is read before the source file is preprocessed.
REM -I: Adds a specified directory to the search path for include files.
REM -std: Specify the language stanard to compile for.
REM -ansi: Alias for -std=c89


:standalone
    SET STANDALONE_FILE = %~dp0guttural\guttural.c
    SET MACROS=/DGUTTURAL_DEBUG
    SET COMPILER_FLAGS=/nologo /Zi /Fobuild\ /Fdbuild\ /c /I "guttural\include"

    FOR /r %%f IN ("guttural\src\*.c") DO cl %COMPILER_FLAGS% "%%f" %MACROS%

    cl %COMPILER_FLAGS% guttural\guttural.c %MACROS%

    PUSHD build

    SET LINKER_FLAGS=/NOLOGO /DEBUG

    link %LINKER_FLAGS% /OUT:guttural.exe *.obj

    POPD

    GOTO end

:msvc
    SET COMPILER=cl
    SET CL_FLAGS=/nologo /I "guttural\include" /Fobuild\
    SET CL_MACROS=/DGUTTURAL_DEBUG

    FOR /r %%f IN (guttural\src\*.c) DO %COMPILER% %CL_FLAGS% "%%f" %CL_MACROS%

    GOTO end

:clang
    SET CLANG_FLAGS=-O0 -g -c -I "guttural\include"

:end
    ECHO "Finished"
