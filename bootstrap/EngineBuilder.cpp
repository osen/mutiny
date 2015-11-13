#include "EngineBuilder.h"
#include "Environment.h"
#include "cwrapper.h"
#include "FileInfo.h"
#include "Util.h"

#include <iostream>

std::shared_ptr<EngineBuilder> EngineBuilder::create(std::shared_ptr<Environment> environment)
{
  static EngineBuilder s;
  std::shared_ptr<EngineBuilder> rtn(new EngineBuilder(s));

  rtn->environment = environment;
  rtn->srcDir = environment->getPrefix() + "/src/mutiny";

  std::cout << "Mutiny Source Directory: " << rtn->srcDir << std::endl;

  rtn->scanSource(rtn->srcDir);
  rtn->prepareDirectories();

  for(int i = 0; i < rtn->sourceUnits.size(); i++)
  {
    std::string objPath = "temp/linux/obj/mutiny/" +
      rtn->sourceUnits.at(i)->getBaseName() +
      ".o";

    std::cout << "Compiling: " << rtn->sourceUnits.at(i)->getAbsolutePath() << std::endl;
    std::string result = Util::execute("g++ -std=c++11 -c " +
      rtn->sourceUnits.at(i)->getAbsolutePath() +
      " -o " +
      objPath);

    std::cout << result << std::endl;
  }

  return rtn;
}

void EngineBuilder::prepareDirectories()
{
  try { Dir::mkdir("temp"); } catch(std::exception& e) { }
  try { Dir::mkdir("temp/linux"); } catch(std::exception& e) { }
  try { Dir::mkdir("temp/linux/obj"); } catch(std::exception& e) { }
  try { Dir::mkdir("temp/linux/obj/mutiny"); } catch(std::exception& e) { }
  try { Dir::mkdir("temp/linux/obj/game"); } catch(std::exception& e) { }

  try { Dir::mkdir("build"); } catch(std::exception& e) { }
  try { Dir::mkdir("build/linux"); } catch(std::exception& e) { }
  try { Dir::mkdir("build/linux/bin"); } catch(std::exception& e) { }
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
        }
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
