@echo off
IF NOT DEFINED VCVARSLOADED (
    call D:\shell\vcvars140.bat
    set VCVARSLOADED=1
)
echo Building for [92mWin32[0m
pushd d:\wasapi\build
cl -EHsc ..\ofstream.cpp
popd