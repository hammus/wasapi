@echo off
call D:\shell\vcvars140.bat
echo Building for [92mWin32[0m
pushd d:\wasapi\build
cl -EHsc ..\ofstream.cpp
popd