@echo off

mkdir ..\bin > nul 2>&1
mkdir temp > nul 2>&1

:msvc14
echo ********************************************
echo *** Trying Microsoft Visual Studio 14... ***
echo ********************************************
call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" || goto msvc12
cl /EHsc *.cpp /Fotemp\ /Fe..\bin\mutt && goto done

:msvc12
echo.
echo ********************************************
echo *** Trying Microsoft Visual Studio 12... ***
echo ********************************************
call "C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\vcvarsall.bat" || goto msvc11
cl /EHsc *.cpp /Fotemp\ /Fe..\bin\mutt && goto done

:msvc11
echo.
echo ********************************************
echo *** Trying Microsoft Visual Studio 11... ***
echo ********************************************
call "C:\Program Files (x86)\Microsoft Visual Studio 11.0\VC\vcvarsall.bat" || goto msvc10
cl /EHsc *.cpp /Fotemp\ /Fe..\bin\mutt && goto done

:msvc10
echo.
echo ********************************************
echo *** Trying Microsoft Visual Studio 10... ***
echo ********************************************
call "C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\vcvarsall.bat" || goto gcc
cl /EHsc *.cpp /Fotemp\ /Fe..\bin\mutt && goto done

:gcc
echo.
echo ********************************
echo *** Trying GNU C++ Compiler  ***
echo ********************************
g++ *.cpp -o ..\bin\mutt && goto done

:clang
echo.
echo *************************************
echo *** Trying LLVM / Clang Compiler  ***
echo *************************************
clang++ *.cpp -o ..\bin\mutt && goto done

echo.
echo !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
echo !!! Failed to find a C++ compiler to build Mutt !!!
echo !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
pause

:done
rd /s /q temp > nul 2>&1