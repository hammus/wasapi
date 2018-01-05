@echo off
call D:\shell\vcvars140.bat
echo Building for [92mWin32[0m
cl -EHsc ofstream.cpp build/ofstream.exe