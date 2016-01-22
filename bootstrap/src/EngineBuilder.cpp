#include "EngineBuilder.h"
#include "Environment.h"
#include "cwrapper.h"
#include "FileInfo.h"
#include "Util.h"
#include "Compiler.h"
#include "features.h"

#include <iostream>

shared<EngineBuilder> EngineBuilder::create(shared<Environment> environment)
{
  shared<EngineBuilder> rtn = alloc_shared<EngineBuilder>();

  rtn->environment = environment;
  rtn->srcDir = environment->getPrefix() + Util::fixPath("/src/mutiny");

  std::cout << "Mutiny Source Directory: " << rtn->srcDir << std::endl;

  rtn->scanSource(rtn->srcDir);
  rtn->prepareDirectories();

  return rtn;
}

void EngineBuilder::removeOrphanedObjects()
{
  std::string objDir = Util::fixPath("temp/" + std::string(PLATFORM_NAME) + "/obj/mutiny");

  shared<Dir> dir = Dir::opendir(objDir);
  shared<Dirent> dirent = dir->readdir();
  std::vector<std::string> toDelete;

  while(dirent.get() != NULL)
  {
    if(dirent->d_name().at(0) == '.')
    {
      dirent = dir->readdir();
      continue;
    }

    bool found = false;

    for(int i = 0; i < sourceUnits.size(); i++)
    {
      if(sourceUnits.at(i)->getBaseName() == FileInfo::getBaseName(objDir + DIR_CHAR + dirent->d_name()))
      {
        found = true;
        break;
      }
    }

    if(found == false)
    {
      toDelete.push_back(objDir + DIR_CHAR + dirent->d_name());
    }

    dirent = dir->readdir();
  }

  for(int i = 0; i < toDelete.size(); i++)
  {
    std::cout << "Deleting: " << toDelete.at(i) << std::endl;
    Dir::remove(toDelete.at(i));
  }
}

void EngineBuilder::buildOutOfDateObjects()
{
  shared<Compiler> compiler = Compiler::create(environment);

  if(PLATFORM_NAME == std::string("windows"))
  {
    compiler->addIncludeDirectory(environment->getPrefix() + Util::fixPath("/include"));
  }

  for(int i = 0; i < sourceUnits.size(); i++)
  {
    std::string objPath = Util::fixPath("temp/" + 
      std::string(PLATFORM_NAME) + "/obj/mutiny/") +
      sourceUnits.at(i)->getBaseName() +
      "." + compiler->getObjectSuffix();

    try
    {
      shared<FileInfo> objectInfo = FileInfo::create(objPath);

      if(objectInfo->getModified() > sourceUnits.at(i)->getModified())
      {
        //std::cout << "Up to date: " << sourceUnits.at(i)->getFileName() << std::endl;
        continue;
      }
    }
    catch(std::exception& e) { }

    //std::cout << "Compiling: " << sourceUnits.at(i)->getFileName() << std::endl;
    //std::string result = Util::execute("g++ -std=c++11 -c " +
    //  sourceUnits.at(i)->getAbsolutePath() +
    //  " -o " +
    //  objPath);

    compiler->compile(sourceUnits.at(i)->getAbsolutePath(), objPath);

    //std::cout << result << std::endl;
  }
}

void EngineBuilder::prepareDirectories()
{
  Dir::mkdir_r(Util::fixPath("temp/" + std::string(PLATFORM_NAME)
    + "/obj/mutiny"));
}

void EngineBuilder::scanSource(std::string rootDir)
{
  shared<Dir> dir = Dir::opendir(rootDir);
  shared<Dirent> dirent = dir->readdir();

  while(dirent.get() != NULL)
  {
    if(dirent->d_name().at(0) != '.')
    {
      try
      {
        scanSource(rootDir + DIR_CHAR + dirent->d_name());
      }
      catch(std::exception& e)
      {
        if(FileInfo::getSuffix(dirent->d_name()) == "cpp")
        {
          sourceUnits.push_back(SourceFileInfo::create(rootDir + DIR_CHAR + dirent->d_name()));
        }
      }
    }

    dirent = dir->readdir();
  }  
}

