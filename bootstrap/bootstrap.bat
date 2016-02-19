@echo off

mkdir ..\bin > nul 2>&1
mkdir ..\lib > nul 2>&1
mkdir ..\include > nul 2>&1
mkdir temp > nul 2>&1

:msvc14
echo ********************************************
echo *** Trying Microsoft Visual Studio 14... ***
echo ********************************************
call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" || goto msvc12
cl /EHsc src\*.cpp /Fotemp\ /Fe..\bin\mutt && goto done

:msvc12
echo.
echo ********************************************
echo *** Trying Microsoft Visual Studio 12... ***
echo ********************************************
call "C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\vcvarsall.bat" || goto msvc11
cl /EHsc src\*.cpp /Fotemp\ /Fe..\bin\mutt && goto done

:msvc11
echo.
echo ********************************************
echo *** Trying Microsoft Visual Studio 11... ***
echo ********************************************
call "C:\Program Files (x86)\Microsoft Visual Studio 11.0\VC\vcvarsall.bat" || goto msvc10
cl /EHsc src\*.cpp /Fotemp\ /Fe..\bin\mutt && goto done

:msvc10
echo.
echo ********************************************
echo *** Trying Microsoft Visual Studio 10... ***
echo ********************************************
call "C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\vcvarsall.bat" || goto clang
cl /EHsc src\*.cpp /Fotemp\ /Fe..\bin\mutt && goto done

:clang
echo.
echo ****************************************
echo *** Trying LLVM / Clang Compiler...  ***
echo ****************************************
clang++ src\*.cpp -o ..\bin\mutt.exe && goto done

:gcc
echo.
echo ***********************************
echo *** Trying GNU C++ Compiler...  ***
echo ***********************************
g++ src\*.cpp -o ..\bin\mutt && goto done

echo.
echo !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
echo !!! Failed to find a C++ compiler to build Mutt !!!
echo !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
pause

:done
rd /s /q temp > nul 2>&1
cd windows
build_dependencies.bat
cd ..
