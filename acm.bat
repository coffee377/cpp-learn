@ECHO OFF
chcp 65001 >NUL
:: 获取当前目录
set current_dir=%~dp0
@echo %current_dir%

PUSHD "%~dp0"
CLS
SET title=Input Title Here
REM 获取当前目录下的可执行文件（假设可执行文件名为acm.exe）
set executable=%current_dir%acm.exe
REM 目标目录为系统盘的System32目录
set destination=%SystemRoot%
rem 定义要删除的文件路径
set fileToDelete=%SystemRoot%\acm.exe

:MainMenu
CLS
ECHO.
ECHO ACM 环境配置操作：
ECHO ----------------
ECHO  1 安装
ECHO  2 卸载
ECHO  3 退出
ECHO ----------------
ECHO.
ECHO 请选择选项[1/2/3]：
ECHO.
SET /p answer=
IF %answer%==1 CALL :SUB1
IF %answer%==2 CALL :SUB2
IF %answer%==3 GOTO :EOF
GOTO MainMenu

:SUB1
REM 检查可执行文件是否存在
if not exist %executable% (
    echo 可执行文件 %executable% 不存在，请检查。
    pause
    exit /b 1
)
REM 复制文件到System32目录，需要管理员权限
echo 正在复制文件 %executable% 到 %destination%...
copy "%executable%" "%destination%"

REM 检查复制是否成功
if %errorlevel% equ 0 (
    echo acm 安装成功
) else (
    echo 文件安装失败，请检查权限或文件状态。
)
pause
GOTO :EOF

:SUB2
rem 检查文件是否存在
if exist "%fileToDelete%" (
    rem 如果文件存在，尝试删除该文件
    del /F /Q "%fileToDelete%"
    if %errorlevel% equ 0 (
        echo %fileToDelete% 已成功卸载。
    ) else (
        echo 卸载 %fileToDelete% 时出错。
    )
) else (
    echo %fileToDelete% 不存在！！！
)

pause
GOTO :EOF

REM POPD