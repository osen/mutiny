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

  rtn->outputDirectory = "build/linux/bin";

  if(environment->getOutputDirectory() != "")
  {
    rtn->outputDirectory = environment->getOutputDirectory();
  }

  rtn->outputFilename = "project";

  if(FileInfo::getFileName(environment->getCompilerName()) == "em++")
  {
    rtn->outputFilename += ".html";
  }

  rtn->scanSource(rtn->srcDir);
  rtn->prepareDirectories();

  return rtn;
}

void ProjectBuilder::removeOrphanedObjects()
{
  std::string objDir = "temp/linux/obj/project";

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
      if(sourceUnits.at(i)->getBaseName() == FileInfo::getBaseName(objDir + "/" + dirent->d_name()))
      {
        found = true;
        break;
      }
    }

    if(found == false)
    {
      toDelete.push_back(objDir + "/" + dirent->d_name());
    }

    dirent = dir->readdir();
  }

  for(int i = 0; i < toDelete.size(); i++)
  {
    std::cout << "Deleting: " << toDelete.at(i) << std::endl;
    Dir::remove(toDelete.at(i));
  }
}

void ProjectBuilder::syncAssetDirectory(std::string directory)
{
  // Add "assets/" + directory
  // for each source file / folder, if exists in dest directory check modified time
  // If it doesnt exist or modified is older, copy it across
  // If folder, do recursion.
}

void ProjectBuilder::removeOrphanedAssets(std::string directory)
{
  // Add "assets/" + directory
  // for each source file / folder, if does not exist in dest directory add to delete list
  // Process file delete list
  // Recursion folder delete list
  // Delete folder delete list
}

void ProjectBuilder::generateOutOfDateOutput()
{
  std::shared_ptr<Compiler> compiler = Compiler::create(environment);

  if(environment->isMutinyAvailable() == true)
  {
    compiler->addObjectDirectory("temp/linux/obj/mutiny");
  }

  compiler->addObjectDirectory("temp/linux/obj/project");

  for(int i = 0; i < libs.size(); i++)
  {
    compiler->addLib(libs.at(i)->getAbsolutePath());
  }

  bool needsRelink = false;

  try
  {
    std::shared_ptr<FileInfo> binInfo = FileInfo::create(outputDirectory + "/" + outputFilename);

    for(int i = 0; i < sourceUnits.size(); i++)
    {
      if(sourceUnits.at(0)->getModified() > binInfo->getModified())
      {
        needsRelink = true;
      }
    }

    for(int i = 0; i < libs.size(); i++)
    {
      if(libs.at(0)->getModified() > binInfo->getModified())
      {
        needsRelink = true;
      }
    }
  }
  catch(std::exception& e)
  {
    needsRelink = true;
  }

  if(needsRelink == false) return;

  std::cout << "Linking..." << std::endl;
  compiler->link(outputDirectory + "/" + outputFilename);

  removeOrphanedAssets("");
  syncAssetDirectory("");
}

void ProjectBuilder::buildOutOfDateObjects()
{
  std::shared_ptr<Compiler> compiler = Compiler::create(environment);
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

  if(environment->getOutputDirectory() == "")
  {
    try { Dir::mkdir("build"); } catch(std::exception& e) { }
    try { Dir::mkdir("build/linux"); } catch(std::exception& e) { }
    try { Dir::mkdir("build/linux/bin"); } catch(std::exception& e) { }
  }
  else
  {
    try { Dir::mkdir(environment->getOutputDirectory()); } catch(std::exception& e) { }
  }
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
        else if(FileInfo::getSuffix(dirent->d_name()) == "so")
        {
          libs.push_back(FileInfo::create(rootDir + "/" + dirent->d_name()));
        }
      }
    }

    dirent = dir->readdir();
  }  
}

