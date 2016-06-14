@echo off

set CMAKE_ROOT=cmake-3.6.0-rc1-win32-x86
set CMAKE_PACKAGE=%CMAKE_ROOT%.zip

set FREEGLUT_ROOT=freeglut-3.0.0
set FREEGLUT_PACKAGE=%FREEGLUT_ROOT%.zip

set OPENAL_ROOT=openal-soft-1.17.1
set OPENAL_PACKAGE=%OPENAL_ROOT%.zip

set GLEW_ROOT=glew-1.13.0
set GLEW_PACKAGE=%GLEW_ROOT%.zip

set LIBOGG_ROOT=libogg-1.3.2
set LIBOGG_PACKAGE=%LIBOGG_ROOT%.zip

set LIBVORBIS_ROOT=libvorbis-1.3.5
set LIBVORBIS_PACKAGE=%LIBVORBIS_ROOT%.zip

unzip %CMAKE_PACKAGE%

unzip %FREEGLUT_PACKAGE%
cd %FREEGLUT_ROOT%
mkdir build
cd build
..\..\%CMAKE_ROOT%\bin\cmake -G "MinGW Makefiles" ..
..\..\%CMAKE_ROOT%\bin\cmake --build . --config Release
copy lib\libfreeglut_static.a ..\..\..\..\lib\libfreeglut.a
mkdir ..\..\..\..\include\GL
xcopy /s /e ..\include\GL ..\..\..\..\include\GL
cd ..
cd ..

unzip %OPENAL_PACKAGE%
cd %OPENAL_ROOT%
mkdir build
cd build
..\..\%CMAKE_ROOT%\bin\cmake -G "MinGW Makefiles" -DLIBTYPE=STATIC ..
..\..\%CMAKE_ROOT%\bin\cmake --build . --config Release
copy libOpenAL32.a ..\..\..\..\lib\libopenal.a
mkdir ..\..\..\..\include\AL
xcopy /s /e ..\include\AL ..\..\..\..\include\AL
cd ..
cd ..

unzip %GLEW_PACKAGE%
cd %GLEW_ROOT%
cd build\cmake
mkdir build
cd build
..\..\..\..\%CMAKE_ROOT%\bin\cmake -G "MinGW Makefiles" ..
..\..\..\..\%CMAKE_ROOT%\bin\cmake --build . --config Release
copy lib\libglew32.a ..\..\..\..\..\..\lib\libglew.a
xcopy /s /e ..\..\..\include\GL ..\..\..\..\..\..\include\GL
cd ..
cd ..
cd ..
cd ..

unzip %LIBOGG_PACKAGE%
copy libogg.cmake %LIBOGG_ROOT%\CMakeLists.txt
cd %LIBOGG_ROOT%
mkdir build
cd build
..\..\%CMAKE_ROOT%\bin\cmake -G "MinGW Makefiles" ..
..\..\%CMAKE_ROOT%\bin\cmake --build . --config Release
copy liblibogg.a ..\..\..\..\lib\libogg.a
mkdir ..\..\..\..\include\ogg
xcopy /s /e ..\include\ogg\*.h ..\..\..\..\include\ogg
cd ..
cd ..

unzip %LIBVORBIS_PACKAGE%
copy libvorbis.cmake %LIBVORBIS_ROOT%\CMakeLists.txt
cd %LIBVORBIS_ROOT%
mkdir build
cd build
..\..\%CMAKE_ROOT%\bin\cmake -G "MinGW Makefiles" -DOGG_INCLUDE_DIR=..\..\%LIBOGG_ROOT%\include ..
..\..\%CMAKE_ROOT%\bin\cmake --build . --config Release
copy liblibvorbis.a ..\..\..\..\lib\libvorbis.a
copy liblibvorbisfile.a ..\..\..\..\lib\libvorbisfile.a
mkdir ..\..\..\..\include\vorbis
xcopy /s /e ..\include\vorbis\*.h ..\..\..\..\include\vorbis
cd ..
cd ..
