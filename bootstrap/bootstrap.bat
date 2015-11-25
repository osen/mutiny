@echo off

call "C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\vcvarsall.bat"

mkdir ..\bin
mkdir temp
cl /EHsc *.cpp /Fotemp\ /Fe..\bin\mutt
rd /s /q temp