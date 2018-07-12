@echo on

set QT_ENV_PATH=D:\Qt\Qt5.5.1\5.5\mingw492_32\bin\qtenv2.bat

set CUR_PATH=%~dp0
set TARGET_NAME=%CUR_PATH%build\bin\VideoTargetMark.exe
set DEPLOY_DIR=%CUR_PATH%deploy\
set DEPLOY_OPTION=-opengl -test

set EXEC_NAME=%DEPLOY_DIR%VideoTargetMark.exe
set RELEASE_NAME=%DEPLOY_DIR%VideoTargetMark_version_not_defined.exe
set LATEST_NAME=%DEPLOY_DIR%VideoTargetMark_latest.exe
if exist "cur_version.bat" call cur_version.bat 

call %QT_ENV_PATH%

echo Cleaning old deploy stuffs ...
rmdir /S /Q  %DEPLOY_DIR%
echo Creating new deply directory ...
mkdir %DEPLOY_DIR%
echo Copying target program ...
echo %TARGET_NAME%  %RELEASE_NAME%
copy /B %TARGET_NAME% %EXEC_NAME%
echo Deploying ...
windeployqt.exe %DEPLOY_OPTION% %EXEC_NAME%

echo Copying opencv relative .dll files ...
copy /B %CUR_PATH%opencv3\lib\libopencv_imgproc300.dll %DEPLOY_DIR%
copy /B %CUR_PATH%opencv3\lib\libopencv_highgui300.dll %DEPLOY_DIR%
copy /B %CUR_PATH%opencv3\lib\libopencv_core300.dll %DEPLOY_DIR%
copy /B %CUR_PATH%opencv3\lib\libopencv_ml300.dll %DEPLOY_DIR%
copy /B %CUR_PATH%opencv3\lib\libopencv_imgproc300.dll %DEPLOY_DIR%
copy /B %CUR_PATH%opencv3\lib\libopencv_objdetect300.dll %DEPLOY_DIR%
copy /B %CUR_PATH%opencv3\lib\libopencv_videoio300.dll %DEPLOY_DIR%
copy /B %CUR_PATH%opencv3\lib\libopencv_imgcodecs300.dll %DEPLOY_DIR%
copy /B %CUR_PATH%opencv3\lib\opencv_ffmpeg300.dll %DEPLOY_DIR%

echo Starting boxing ...
PATH=%PATH%;%CUR_PATH%tool
enigmavbconsole.exe %CUR_PATH%VideoTargetMark.evb
set BOXED_NAME=%DEPLOY_DIR%VideoTargetMark_boxed.exe
move /Y %BOXED_NAME% %RELEASE_NAME%
copy /Y %RELEASE_NAME% %LATEST_NAME%

:: send fw to ftpserver
:: FIXME: hardcoded url
echo open 172.16.0.5 > temp.ftp
echo anonymous>> temp.ftp
echo anonymous>> temp.ftp
echo cd 02_marktool >> temp.ftp
echo binary >> temp.ftp
echo put %RELEASE_NAME% >> temp.ftp
:: echo put %LATEST_NAME% >> temp.ftp
echo bye >> temp.ftp
ftp -s:temp.ftp  

::pause