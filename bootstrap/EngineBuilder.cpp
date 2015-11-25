#include "EngineBuilder.h"
#include "Environment.h"
#include "cwrapper.h"
#include "FileInfo.h"
#include "Util.h"
#include "Compiler.h"

#include <iostream>

std::shared_ptr<EngineBuilder> EngineBuilder::create(std::shared_ptr<Environment> environment)
{
  static EngineBuilder s;
  std::shared_ptr<EngineBuilder> rtn(new EngineBuilder(s));

  rtn->environment = environment;
  rtn->srcDir = environment->getPrefix() + Util::fixPath("/src/mutiny");

  std::cout << "Mutiny Source Directory: " << rtn->srcDir << std::endl;

  rtn->scanSource(rtn->srcDir);
  rtn->prepareDirectories();

  return rtn;
}

void EngineBuilder::removeOrphanedObjects()
{
  std::string objDir = Util::fixPath("temp/linux/obj/mutiny");

  std::shared_ptr<Dir> dir = Dir::opendir(objDir);
  std::shared_ptr<Dirent> dirent = dir->readdir();
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
  std::shared_ptr<Compiler> compiler = Compiler::create(environment);

  if(compiler->getName() == "cl")
  {
    compiler->addIncludeDirectory(environment->getPrefix() + Util::fixPath("/import/include"));
  }

  for(int i = 0; i < sourceUnits.size(); i++)
  {
    std::string objPath = Util::fixPath("temp/linux/obj/mutiny/") +
      sourceUnits.at(i)->getBaseName() +
      "." + compiler->getObjectSuffix();

    try
    {
      std::shared_ptr<FileInfo> objectInfo = FileInfo::create(objPath);

      if(objectInfo->getModified() > sourceUnits.at(i)->getModified())
      {
        std::cout << "Up to date: " << sourceUnits.at(i)->getFileName() << std::endl;
        continue;
      }
    }
    catch(std::exception& e) { }

    std::cout << "Compiling: " << sourceUnits.at(i)->getFileName() << std::endl;
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
  try { Dir::mkdir(Util::fixPath("temp")); } catch(std::exception& e) { }
  try { Dir::mkdir(Util::fixPath("temp/linux")); } catch(std::exception& e) { }
  try { Dir::mkdir(Util::fixPath("temp/linux/obj")); } catch(std::exception& e) { }
  try { Dir::mkdir(Util::fixPath("temp/linux/obj/mutiny")); } catch(std::exception& e) { }
}

void EngineBuilder::scanSource(std::string rootDir)
{
  std::shared_ptr<Dir> dir = Dir::opendir(rootDir);
  std::shared_ptr<Dirent> dirent = dir->readdir();

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

