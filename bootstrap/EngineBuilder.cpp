#include "EngineBuilder.h"
#include "Environment.h"
#include "cwrapper.h"
#include "FileInfo.h"

#include <iostream>

std::shared_ptr<EngineBuilder> EngineBuilder::create(std::shared_ptr<Environment> environment)
{
  static EngineBuilder s;
  std::shared_ptr<EngineBuilder> rtn(new EngineBuilder(s));

  rtn->environment = environment;
  rtn->srcDir = environment->getPrefix() + "/src/mutiny";

  std::cout << "Mutiny Source Directory: " << rtn->srcDir << std::endl;

  rtn->scanSource(rtn->srcDir);

  return rtn;
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
        scanSource(rootDir + "/" + dirent->d_name());
      }
      catch(std::exception& e)
      {
        if(FileInfo::getSuffix(dirent->d_name()) == "cpp")
        {
          sourceUnits.push_back(SourceFileInfo::create(rootDir + "/" + dirent->d_name()));
          //std::cout << "Source: " << dirent->d_name() << std::endl;
        }
        //else if(FileInfo::getSuffix(dirent->d_name()) == "h")
        //{
        //  std::cout << "Header: " << dirent->d_name() << std::endl;
        //}
      }
    }

    dirent = dir->readdir();
  }  
}

void EngineBuilder::buildIfNeeded()
{
  if(needsBuilding() == false)
  {
    return;
  }
}

bool EngineBuilder::needsBuilding()
{
  return false;
}
