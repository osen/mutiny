#include "ProjectBuilder.h"
#include "Environment.h"
#include "cwrapper.h"
#include "FileInfo.h"
#include "Util.h"
#include "Compiler.h"

#include <iostream>

std::shared_ptr<ProjectBuilder> ProjectBuilder::create(std::shared_ptr<Environment> environment)
{
  static ProjectBuilder s;
  std::shared_ptr<ProjectBuilder> rtn(new ProjectBuilder(s));

  rtn->environment = environment;
  rtn->srcDir = "assets";

  std::cout << "Project Directory: " << rtn->srcDir << std::endl;

  rtn->scanSource(rtn->srcDir);
  rtn->prepareDirectories();

  return rtn;
}

void ProjectBuilder::removeOrphanedObjects()
{
  // TODO:
  // Go through each .o file in obj dir
  // If no sourceUnit exists which matches it then remove it
}

void ProjectBuilder::generateOutOfDateOutput()
{
  std::shared_ptr<Compiler> compiler = Compiler::create();
  compiler->addObjectDirectory("temp/linux/obj/mutiny");
  compiler->addObjectDirectory("temp/linux/obj/project");

  std::cout << "Linking..." << std::endl;
  compiler->link("build/linux/bin/project");
}

void ProjectBuilder::buildOutOfDateObjects()
{
  std::shared_ptr<Compiler> compiler = Compiler::create();
  compiler->addIncludeDirectory(environment->getPrefix() + "/src");

  for(int i = 0; i < sourceUnits.size(); i++)
  {
    std::string objPath = "temp/linux/obj/project/" +
      sourceUnits.at(i)->getBaseName() +
      ".o";

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

void ProjectBuilder::prepareDirectories()
{
  try { Dir::mkdir("temp"); } catch(std::exception& e) { }
  try { Dir::mkdir("temp/linux"); } catch(std::exception& e) { }
  try { Dir::mkdir("temp/linux/obj"); } catch(std::exception& e) { }
  try { Dir::mkdir("temp/linux/obj/project"); } catch(std::exception& e) { }

  try { Dir::mkdir("build"); } catch(std::exception& e) { }
  try { Dir::mkdir("build/linux"); } catch(std::exception& e) { }
  try { Dir::mkdir("build/linux/bin"); } catch(std::exception& e) { }
}

void ProjectBuilder::scanSource(std::string rootDir)
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

