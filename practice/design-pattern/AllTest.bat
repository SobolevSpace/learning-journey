@echo off
echo Testing Singleton pattern...
g++ Singleton.cpp -o Singleton.exe
if errorlevel 1 (
    echo Compile failed!
    pause
    exit /b 1
)
Singleton.exe
pause
