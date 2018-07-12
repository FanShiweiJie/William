:: Used for GitLab CI config

:: Setting Qt environment first.
:: FIXME: File path hardcoded, should not depend on runners.
pushd .\
call D:\Qt\Qt5.5.1\5.5\mingw492_32\bin\qtenv2.bat

popd

:: git submodule init
:: git submodule update

qmake.exe VideoTargetMark.pro -r -spec win32-g++

:: Try walk acrossing
gen_version.sh build/version.h
mingw32-make.exe

:: check if success
set COMPILE_RESULT=%ERRORLEVEL%
echo "Compile result: %COMPILE_RESULT%"

if %COMPILE_RESULT% neq 0 (exit \B 1)

echo "Starting packing ..."
deploy.bat
if exist "deploy\VideoTargetMark_latest.exe" (exit \B 0) else (exit \B 1)