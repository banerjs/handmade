@echo off

set projectdir="C:\Users\Siddhartha\Documents\Code\handmade"

mkdir %projectdir%/build
pushd %projectdir%/build
cl -Zi ../code/win32_handmade.cpp user32.lib gdi32.lib
popd
