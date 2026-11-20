::@echo off
:: > Setup required Environment
:: -------------------------------------
set COMPILER_DIR=C:\raylib\w64devkit\bin
set PATH=%PATH%;%COMPILER_DIR%
cd %~dp0
:: .
:: > Compile simple .rc file
:: ----------------------------
cd ..\..\src
cmd /c windres escaping_696.rc -o escaping_696.rc.data
:: .
:: > Generating project
:: --------------------------
cmd /c mingw32-make -f Makefile ^
PROJECT_NAME=escaping_696 ^
PROJECT_VERSION=1.0 ^
PROJECT_DESCRIPTION="What secrets could lie in house number 696...?" ^
PROJECT_INTERNAL_NAME=escaping_696 ^
PROJECT_PLATFORM=PLATFORM_DESKTOP ^
PROJECT_SOURCE_FILES="escaping_696.c" ^
BUILD_MODE="RELEASE"
:: > Return to scripts directory
:: -----------------------------
cd ..\projects\scripts