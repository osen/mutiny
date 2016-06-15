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
cl /EHsc src\*.cpp /Fotemp\ /Fe..\bin\mutt && goto deps_msvc

:msvc12
echo.
echo ********************************************
echo *** Trying Microsoft Visual Studio 12... ***
echo ********************************************
call "C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\vcvarsall.bat" || goto msvc11
cl /EHsc src\*.cpp /Fotemp\ /Fe..\bin\mutt && goto deps_msvc

:msvc11
echo.
echo ********************************************
echo *** Trying Microsoft Visual Studio 11... ***
echo ********************************************
call "C:\Program Files (x86)\Microsoft Visual Studio 11.0\VC\vcvarsall.bat" || goto msvc10
cl /EHsc src\*.cpp /Fotemp\ /Fe..\bin\mutt && goto deps_msvc

:msvc10
echo.
echo ********************************************
echo *** Trying Microsoft Visual Studio 10... ***
echo ********************************************
call "C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\vcvarsall.bat" || goto clang
cl /EHsc src\*.cpp /Fotemp\ /Fe..\bin\mutt && goto deps_msvc

:clang
echo.
echo ****************************************
echo *** Trying LLVM / Clang Compiler...  ***
echo ****************************************
clang++ src\*.cpp -o ..\bin\mutt.exe && goto deps_mingw

:gcc
echo.
echo ***********************************
echo *** Trying GNU C++ Compiler...  ***
echo ***********************************
g++ src\*.cpp -o ..\bin\mutt && goto deps_mingw

echo.
echo !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
echo !!! Failed to find a C++ compiler to build Mutt !!!
echo !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
cd windows
7z x i686-4.9.1-release-posix-dwarf-rt_v3-rev2.7z
cd ..
set PATH=%PATH%;%~dp0\windows\mingw32\bin
g++ -D INTERNAL_GCC src\*.cpp -o ..\bin\mutt
copy windows\mingw32\bin\libgcc_s_dw2-1.dll ..\bin
copy "windows\mingw32\bin\libstdc++-6.dll" ..\bin
copy windows\mingw32\bin\libwinpthread-1.dll ..\bin
goto deps_mingw

:deps_msvc
rd /s /q temp > nul 2>&1
cd windows
build_dependencies_msvc.bat
cd ..
goto done

:deps_mingw
rd /s /q temp > nul 2>&1
cd windows
build_dependencies_mingw.bat
cd ..
goto done

:done
