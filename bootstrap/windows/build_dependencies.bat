@echo off

set CMAKE_ROOT=cmake-3.4.2-win32-x86
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

cmd /C unzip.bat %CMAKE_PACKAGE%

cmd /C unzip.bat %FREEGLUT_PACKAGE%
cd %FREEGLUT_ROOT%
mkdir build
cd build
..\..\%CMAKE_ROOT%\bin\cmake ..
..\..\%CMAKE_ROOT%\bin\cmake --build . --config Release
copy lib\Release\freeglut_static.lib ..\..\..\..\lib\freeglut.lib
mkdir ..\..\..\..\include\GL
xcopy /s /e ..\include\GL ..\..\..\..\include\GL
cd ..
cd ..

cmd /C unzip.bat %OPENAL_PACKAGE%
cd %OPENAL_ROOT%
mkdir build
cd build
..\..\%CMAKE_ROOT%\bin\cmake ..
..\..\%CMAKE_ROOT%\bin\cmake --build . --config Release
copy Release\OpenAL32.lib ..\..\..\..\lib\openal.lib
mkdir ..\..\..\..\include\AL
xcopy /s /e ..\include\AL ..\..\..\..\include\AL
cd ..
cd ..

cmd /C unzip.bat %GLEW_PACKAGE%
cd %GLEW_ROOT%
cd build\cmake
mkdir build
cd build
..\..\..\..\%CMAKE_ROOT%\bin\cmake ..
..\..\..\..\%CMAKE_ROOT%\bin\cmake --build . --config Release
copy lib\Release\libglew32.lib ..\..\..\..\..\..\lib\glew.lib
xcopy /s /e ..\..\..\include\GL ..\..\..\..\..\..\include\GL
cd ..
cd ..
cd ..
cd ..

cmd /C unzip.bat %LIBOGG_PACKAGE%
copy libogg.cmake %LIBOGG_ROOT%\CMakeLists.txt
cd %LIBOGG_ROOT%
mkdir build
cd build
..\..\%CMAKE_ROOT%\bin\cmake ..
..\..\%CMAKE_ROOT%\bin\cmake --build . --config Release
copy Release\libogg.lib ..\..\..\..\lib\ogg.lib
mkdir ..\..\..\..\include\ogg
xcopy /s /e ..\include\ogg\*.h ..\..\..\..\include\ogg
cd ..
cd ..

cmd /C unzip.bat %LIBVORBIS_PACKAGE%
copy libvorbis.cmake %LIBVORBIS_ROOT%\CMakeLists.txt
cd %LIBVORBIS_ROOT%
mkdir build
cd build
..\..\%CMAKE_ROOT%\bin\cmake -DOGG_INCLUDE_DIR=..\..\%LIBOGG_ROOT%\include ..
..\..\%CMAKE_ROOT%\bin\cmake --build . --config Release
copy Release\libvorbis.lib ..\..\..\..\lib\vorbis.lib
copy Release\libvorbisfile.lib ..\..\..\..\lib\vorbisfile.lib
mkdir ..\..\..\..\include\vorbis
xcopy /s /e ..\include\vorbis\*.h ..\..\..\..\include\vorbis
cd ..
cd ..
