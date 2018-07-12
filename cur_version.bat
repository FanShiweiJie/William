@for /f %%i in ('git describe --tags') do (set GIT_DESC=%%i) 
set RELEASE_NAME=%DEPLOY_DIR%VideoTargetMark-%GIT_DESC%.exe
