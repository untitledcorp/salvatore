@echo off

if not exist "build" mkdir "build"

cd src

set INCLUDE_DIR=..\include
set LIB_DIR=..\lib

g++ -o ../build/salvatore main.cpp qemu_wrapper.cpp vm_manager.cpp -I"%INCLUDE_DIR%\libvirt" -L"%LIB_DIR%" -lvirt-2.0 -lqemu

if %errorlevel% neq 0 (
    echo Build failed!
    pause
    exit /b 1
) else (
    echo Build successful!
    pause
)
