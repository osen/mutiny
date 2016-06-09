#include "Compiler.h"
#include "Util.h"
#include "Environment.h"
#include "FileInfo.h"
#include "features.h"

#include <iostream>

shared<Compiler> Compiler::create(shared<Environment> environment)
{
  shared<Compiler> rtn = alloc_shared<Compiler>();
  rtn->environment = environment;
  rtn->name = environment->getCompilerName();

  rtn->obtainPreEnvironmentScript();

  return rtn;
}

void Compiler::obtainPreEnvironmentScript()
{
  std::string script;

  if(name == "cl")
  {
    try
    {
      script = "call \"C:\\Program Files (x86)\\Microsoft Visual Studio 14.0\\VC\\vcvarsall.bat\"";
      Util::execute(script);
      preEnvironmentScript = script;
      return;
    } catch(std::exception& e){}

    try
    {
      script = "call \"C:\\Program Files (x86)\\Microsoft Visual Studio 12.0\\VC\\vcvarsall.bat\"";
      Util::execute(script);
      preEnvironmentScript = script;
      return;
    } catch(std::exception& e){}

    try
    {
      script = "call \"C:\\Program Files (x86)\\Microsoft Visual Studio 11.0\\VC\\vcvarsall.bat\"";
      Util::execute(script);
      preEnvironmentScript = script;
      return;
    } catch(std::exception& e){}

    try
    {
      script = "call \"C:\\Program Files (x86)\\Microsoft Visual Studio 10.0\\VC\\vcvarsall.bat\"";
      Util::execute(script);
      preEnvironmentScript = script;
      return;
    } catch(std::exception& e){}
  }
}

std::string Compiler::getName()
{
  return name;
}

void Compiler::addIncludeDirectory(std::string directory)
{
  includeDirectories.push_back(directory);
}

std::string Compiler::getObjectSuffix()
{
  if(name == "cl")
  {
    return "obj";
  }

  return "o";
}

std::string Compiler::getExecutableSuffix()
{
  if(FileInfo::getFileName(name) == "em++")
  {
    return "html";
  }

#ifdef EXECUTABLE_SUFFIX
  return EXECUTABLE_SUFFIX;
#endif

  return "";
}

void Compiler::compile(std::string sourceUnit, std::string output)
{
  std::string program = name;
  std::string includeFragment;
  std::string defineFragment;
  std::string debugFragment;

  if(environment->isDebug() == true)
  {
    if(program == "cl")
    {
      debugFragment += " /DDEBUG /Zi";
    }
    else
    {
      debugFragment += " -g";
    }
  }
  else
  {
    if(program == "cl")
    {
      debugFragment += " /Ox /DNDEBUG";
    }
    else
    {
      debugFragment += " -O3";
    }
  }

  for(int i = 0; i < includeDirectories.size(); i++)
  {
    if(program == "cl")
    {
      includeFragment += " /I" + includeDirectories.at(i);
    }
    else
    {
      includeFragment += " -I" + includeDirectories.at(i);
    }
  }

  std::vector<std::string> defines = environment->getDefines();

  if(environment->isMutinyAvailable() == true)
  {
    if(std::string(PLATFORM_NAME) == "windows")
    {
      //if(name == "g++" || name == "clang++")
      //{
        defines.push_back("FREEGLUT_STATIC");
        defines.push_back("GLEW_STATIC");
        defines.push_back("AL_LIBTYPE_STATIC");
      //}
    }
  }

  for(int i = 0; i < defines.size(); i++)
  {
    if(program == "cl")
    {
      defineFragment += " /D" + defines.at(i);
    }
    else
    {
      defineFragment += " -D" + defines.at(i);
    }
  }

  std::string command;

  if(program == "cl")
  {
    command = preEnvironmentScript + " && " + program +
    //command = program +
      " /EHsc /c /DWINDOWS" +
      debugFragment +
      includeFragment +
      defineFragment +
      " " + sourceUnit +
      " /MD" +
      " /Fo" + output;
  }
  else
  {
    command = program + " -c -Wall" +
      debugFragment +
      includeFragment +
      defineFragment +
      " " + sourceUnit +
      " -o" +
      " " + output;
  }

  std::cout << command << std::endl;
  std::string result = Util::execute(command);
}

void Compiler::addObjectDirectory(std::string directory)
{
  objectDirectories.push_back(directory);
}

void Compiler::addLibDirectory(std::string directory)
{
  libDirectories.push_back(directory);
}

void Compiler::addLib(std::string path)
{
  libs.push_back(path);
}

void Compiler::link(std::string output)
{
  std::string program = name;
  std::string debugFragment;
  std::string libsFragment;

  if(environment->isDebug() == true)
  {
    if(program == "cl")
    {
      debugFragment += " /DEBUG";

      if(environment->isMutinyAvailable() == true)
      {
        libsFragment += " /NODEFAULTLIB:freeglut_static.lib /NODEFAULTLIB:freeglut_staticd.lib";
      }
    }
    else
    {
      debugFragment += " -g";
    }
  }
  else
  {
    if(program == "cl")
    {
      if(environment->isMutinyAvailable() == true)
      {
        libsFragment += " /NODEFAULTLIB:freeglut_static.lib";
      }
    }
    else if(FileInfo::getFileName(name) == "em++")
    {
      debugFragment += " -O3";
    }
  }

  std::string objectsFragment = "";

  for(int i = 0; i < objectDirectories.size(); i++)
  {
    objectsFragment += " " + objectDirectories.at(i) + Util::fixPath("/*.") + getObjectSuffix();
  }

  for(int i = 0; i < libDirectories.size(); i++)
  {
    if(name == "cl")
    {
      libsFragment += " /LIBPATH:" + libDirectories.at(i);
    }
    else
    {
      libsFragment += " -L" + libDirectories.at(i);
    }
  }

  for(int i = 0; i < libs.size(); i++)
  {
    libsFragment += " " + libs.at(i);
  }

  if(environment->isMutinyAvailable() == true)
  {
    if(FileInfo::getFileName(name) == "em++")
    {

    }
    else if(name == "cl")
    {
      //libsFragment += " SDL.lib SDLmain.lib SDL_mixer.lib glew32.lib opengl32.lib user32.lib";
      libsFragment += " freeglut.lib glew.lib openal.lib ogg.lib vorbis.lib vorbisfile.lib opengl32.lib user32.lib ole32.lib oleaut32.lib strmiids.lib shell32.lib";
    }
    else if(std::string(PLATFORM_NAME) == "windows")
    {
      libsFragment += " -lglew32 -lfreeglut -lopengl32 -logg -lvorbis -lvorbisfile -lopenal32 -lgdi32 -lwinmm -luser32";
    }
    else
    {
      libsFragment += " -lGL -lGLEW -lglut -logg -lvorbis -lvorbisfile -lopenal";
    }
  }

  std::string command;

  if(FileInfo::getFileName(name) == "em++")
  {
    std::string projectName = environment->getProjectName();
    std::string objectArchives = " temp/" + std::string(PLATFORM_NAME)  + "/obj/" + projectName + ".a";

    if(environment->isMutinyAvailable() == true)
    {
      command = "emar cr" +
        std::string(" temp/" + std::string(PLATFORM_NAME)  + "/obj/mutiny.a") +
        Util::fixPath(" temp/" + std::string(PLATFORM_NAME)  + "/obj/mutiny/*.o");

      std::cout << command << std::endl;
      std::string result1 = Util::execute(command);

      objectArchives = " temp/" + std::string(PLATFORM_NAME)  + "/obj/mutiny.a" + objectArchives;
    }

    command = "emar cr" +
      std::string(" temp/" + std::string(PLATFORM_NAME)  + "/obj/" + projectName + ".a") +
      Util::fixPath(" temp/" + std::string(PLATFORM_NAME)  + "/obj/" + projectName + "/*.o");

    std::cout << command << std::endl;
    std::string result2 = Util::execute(command);

    command = program +
      debugFragment +
      objectArchives +
      " -o" +
      " " + output +
      libsFragment +
      " --preload-file " + Util::fixPath("build/windows/share/" + projectName + "@");

    std::cout << command << std::endl;
    std::string emresult = Util::execute(command);

    return;
  }

  if(program == "cl")
  {
    command = preEnvironmentScript + " && link" +
    //command = "link" +
      debugFragment +
      objectsFragment +
      " /out:" + output +
      " /subsystem:console" +
      libsFragment;
  }
  else
  {
    command = program +
      debugFragment +
      objectsFragment +
      " -o" +
      " " + output +
      libsFragment;
  }

  std::cout << command << std::endl;
  std::string result = Util::execute(command);
}
