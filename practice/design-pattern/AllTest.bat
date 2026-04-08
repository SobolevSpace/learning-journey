@echo off

echo Testing Singleton pattern...
g++ Singleton.cpp -o Singleton.exe
if errorlevel 1 (
    echo Compile failed!
    pause
    exit /b 1
)
Singleton.exe
echo.

echo Testing Factory pattern...
g++ Factory.cpp -o Factory.exe
if errorlevel 1 (
    echo Compile failed!
    pause
    exit /b 1
)
Factory.exe
pause
