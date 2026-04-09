@echo off
setlocal enabledelayedexpansion

set PATTERNS=Singleton Factory Prototype Builder Adapter Bridge Combinator Decorator Facade Proxy Flyweight ChainOfResponsibility Command

for %%p in (%PATTERNS%) do (
    echo Testing %%p pattern...
    g++ %%p.cpp -o %%p.exe
    if errorlevel 1 (
        echo Compile failed!
        pause
        exit /b 1
    )
    %%p.exe
    echo.
)

pause
