#include "ProjectBuilder.h"
#include "Environment.h"
#include "cwrapper.h"
#include "FileInfo.h"
#include "Util.h"
#include "Compiler.h"
#include "features.h"

#include <iostream>

shared<ProjectBuilder> ProjectBuilder::create(shared<Environment> environment)
{
  shared<ProjectBuilder> rtn = alloc_shared<ProjectBuilder>();

  rtn->environment = environment;
  rtn->srcDir = "assets";

  std::cout << "Project Directory: " << rtn->srcDir << std::endl;

  rtn->outputDirectory = Util::fixPath("build/") +
    PLATFORM_NAME;

  if(environment->getOutputDirectory() != "")
  {
    rtn->outputDirectory = environment->getOutputDirectory();
  }

  rtn->obtainOutputFilename();

  rtn->scanForIncludeDirectories(rtn->srcDir);

  if(environment->isMutinyAvailable() == true)
  {
    rtn->includeDirectories.push_back(environment->getPrefix() + DIR_CHAR + "src");
  }

  rtn->scanSource(rtn->srcDir);
  rtn->prepareDirectories();

  return rtn;
}

void ProjectBuilder::removeOrphanedObjects()
{
  std::string objDir = Util::fixPath("temp/"+std::string(PLATFORM_NAME)+"/obj/" + outputFilename);

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
      if(sourceUnits.at(i)->getBaseName() ==
         FileInfo::getBaseName(objDir + DIR_CHAR + dirent->d_name()))
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

void ProjectBuilder::obtainOutputFilename()
{
  outputFilename = FileInfo::getFileName(Dir::getcwd());
}

bool ProjectBuilder::syncAssetDirectory(std::string assetDirectory)
{
  std::vector<shared<FileInfo> > assetDirectories;
  std::vector<shared<FileInfo> > buildAssetDirectories;
  std::vector<std::string> directoryDeleteList;
  bool changed = false;

  std::string buildAssetDirectory = Util::fixPath("build/" +
    std::string(PLATFORM_NAME)+"/share/" + outputFilename);

  FileInfo::scanDirectory(assetDirectory, false, assetDirectories);
  FileInfo::scanDirectory(buildAssetDirectory, false, buildAssetDirectories);
  FileInfo::scanDirectory(assetDirectory, true, assetDirectories);
  FileInfo::scanDirectory(buildAssetDirectory, true, buildAssetDirectories);

  assetDirectory += DIR_CHAR;
  buildAssetDirectory += DIR_CHAR;

  for(int i = assetDirectories.size() - 1; i >= 0; i--)
  {
    bool found = false;

    for(int j = 0; j < buildAssetDirectories.size(); j++)
    {
      if(assetDirectories.at(i)->getAbsolutePath().
           substr(assetDirectory.length()) ==
         buildAssetDirectories.at(j)->getAbsolutePath().
           substr(buildAssetDirectory.length()))
      {
        if(assetDirectories.at(i)->getModified() <=
           buildAssetDirectories.at(j)->getModified())
        {
          found = true;
          break;
        }
      }
    }

    if(found == false)
    {
      if(Dir::isdir(assetDirectories.at(i)->getAbsolutePath()) == true)
      {
        if(Dir::isdir(buildAssetDirectory + assetDirectories.at(i)->
             getAbsolutePath().substr(assetDirectory.length())) == false)
        {
          Dir::mkdir(buildAssetDirectory + assetDirectories.at(i)->
            getAbsolutePath().substr(assetDirectory.length()));
        }
      }
      else
      {
        std::cout << "Syncing Asset: " << assetDirectories.at(i)->getAbsolutePath() << std::endl;

        Util::copyFile(assetDirectories.at(i)->getAbsolutePath(),
          buildAssetDirectory + assetDirectories.at(i)->
          getAbsolutePath().substr(assetDirectory.length()));

        changed = true;
      }
    }
  }

  return changed;
}

void ProjectBuilder::removeOrphanedAssets()
{
  std::vector<shared<FileInfo> > assetDirectories;
  std::vector<shared<FileInfo> > buildAssetDirectories;
  std::vector<std::string> directoryDeleteList;

  std::string assetDirectory = Util::fixPath("assets");
  std::string buildAssetDirectory = Util::fixPath("build/"+std::string(PLATFORM_NAME)+"/share/" + outputFilename);

  FileInfo::scanDirectory(assetDirectory, false, assetDirectories);
  FileInfo::scanDirectory(buildAssetDirectory, false, buildAssetDirectories);
  FileInfo::scanDirectory(assetDirectory, true, assetDirectories);
  FileInfo::scanDirectory(buildAssetDirectory, true, buildAssetDirectories);

  assetDirectory += DIR_CHAR;
  buildAssetDirectory += DIR_CHAR;

  for(int i = 0; i < buildAssetDirectories.size(); i++)
  {
    bool found = false;

    for(int j = 0; j < assetDirectories.size(); j++)
    {
      if(buildAssetDirectories.at(i)->getAbsolutePath().substr(buildAssetDirectory.length()) ==
         assetDirectories.at(j)->getAbsolutePath().substr(assetDirectory.length()))
      {
        found = true;
        break;
      }
    }

    if(found == false)
    {
      directoryDeleteList.push_back(buildAssetDirectories.at(i)->getAbsolutePath());
    }
  }

  for(int i = 0; i < directoryDeleteList.size(); i++)
  {
    //std::cout << "Dir::remove(" << directoryDeleteList.at(i) << ");" << std::endl;
    Dir::remove(directoryDeleteList.at(i));
  }
}

void ProjectBuilder::generateOutOfDateOutput()
{
  shared<Compiler> compiler = Compiler::create(environment);
  std::string outputExecutableName = outputFilename;

  if(compiler->getExecutableSuffix() != "")
  {
    outputExecutableName += "." + compiler->getExecutableSuffix();
  }


  if(environment->isMutinyAvailable() == true)
  {
    compiler->addObjectDirectory(Util::fixPath(
      "temp/"+std::string(PLATFORM_NAME)+"/obj/mutiny"));

    if(PLATFORM_NAME == std::string("windows"))
    {
      if(compiler->getName() != "em++")
      {
        compiler->addLibDirectory(environment->getPrefix() + Util::fixPath("/lib"));
      }
    }
  }

  compiler->addObjectDirectory(Util::fixPath(
    "temp/"+std::string(PLATFORM_NAME)+"/obj/" + outputFilename));

  for(int i = 0; i < libs.size(); i++)
  {
    compiler->addLib(libs.at(i)->getAbsolutePath());
  }

  bool needsRelink = false;
  shared<FileInfo> binInfo;

  try
  {
    binInfo = FileInfo::create(outputDirectory +
      Util::fixPath("/bin/") + outputExecutableName);
  }
  catch(std::exception& e)
  {
    needsRelink = true;
  }

  if(binInfo.get() != NULL)
  {
    std::vector<shared<FileInfo> > objects;

    if(environment->isMutinyAvailable() == true)
    {
      FileInfo::scanDirectory(Util::fixPath(
        "temp/" + std::string(PLATFORM_NAME) + "/obj/mutiny"),
        false, objects);
    }

    FileInfo::scanDirectory(Util::fixPath(
      "temp/" + std::string(PLATFORM_NAME) + "/obj/" + outputFilename),
      false, objects);

    for(int i = 0; i < objects.size(); i++)
    {
      if(objects.at(i)->getModified() > binInfo->getModified())
      {
        needsRelink = true;
        break;
      }
    }

    for(int i = 0; i < libs.size(); i++)
    {
      if(libs.at(0)->getModified() > binInfo->getModified())
      {
        needsRelink = true;
        break;
      }
    }
  }

  removeOrphanedAssets();

  if(syncAssetDirectory("assets") == true)
  {
    if(compiler->getName() == "em++")
    {
      needsRelink = true;
    }
  }

  if(environment->isMutinyAvailable() == true)
  {
    if(syncAssetDirectory(environment->getPrefix() + Util::fixPath("/share/mutiny")) == true)
    {
      if(compiler->getName() == "em++")
      {
        needsRelink = true;
      }
    }
  }

  if(needsRelink == false) return;

  //std::cout << "Linking..." << std::endl;
  compiler->link(outputDirectory + Util::fixPath("/bin/") + outputExecutableName);
}

void ProjectBuilder::buildOutOfDateObjects()
{
  shared<Compiler> compiler = Compiler::create(environment);

  if(environment->isMutinyAvailable() == true)
  {
    compiler->addIncludeDirectory(environment->getPrefix() + Util::fixPath("/src"));

    if(PLATFORM_NAME == std::string("windows"))
    {
      if(compiler->getName() != "em++")
      {
        compiler->addIncludeDirectory(environment->getPrefix() + Util::fixPath("/include"));
      }
    }
  }

  for(int i = 0; i < includeDirectories.size(); i++)
  {
    compiler->addIncludeDirectory(includeDirectories.at(i));
  }

  for(int i = 0; i < sourceUnits.size(); i++)
  {
    std::string objPath = Util::fixPath("temp/"+std::string(PLATFORM_NAME)+"/obj/"+outputFilename+"/" +
      sourceUnits.at(i)->getBaseName() +
      "." + compiler->getObjectSuffix());

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

void ProjectBuilder::prepareDirectories()
{
  try { Dir::mkdir_r(Util::fixPath("temp/"+std::string(PLATFORM_NAME)+"/obj/" + outputFilename)); } catch(std::exception& e) { }

  try { Dir::mkdir_r(Util::fixPath(outputDirectory + "/share/" + outputFilename)); } catch(std::exception& e) { }
  try { Dir::mkdir_r(Util::fixPath(outputDirectory + "/bin")); } catch(std::exception& e) { }
}

void ProjectBuilder::scanSource(std::string rootDir)
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
        if(FileInfo::getSuffix(dirent->d_name()) == "cpp" ||
           FileInfo::getSuffix(dirent->d_name()) == "c")
        {
          //std::cout << "Adding: " << rootDir << DIR_CHAR << dirent->d_name() << std::endl;
          sourceUnits.push_back(SourceFileInfo::create(rootDir + DIR_CHAR + dirent->d_name(), includeDirectories));
        }
        else if(FileInfo::getSuffix(dirent->d_name()) == "so" ||
                FileInfo::getSuffix(dirent->d_name()) == "a" ||
                FileInfo::getSuffix(dirent->d_name()) == "lib")
        {
          libs.push_back(FileInfo::create(rootDir + DIR_CHAR + dirent->d_name()));
        }
      }
    }

    dirent = dir->readdir();
  }
}

void ProjectBuilder::scanForIncludeDirectories(std::string rootDir)
{
  shared<Dir> dir;

  try
  {
    dir = Dir::opendir(rootDir);
  }
  catch(std::exception& e)
  {
    return;
  }

  shared<Dirent> dirent = dir->readdir();

  while(dirent.get() != NULL)
  {
    if(dirent->d_name().at(0) == '.')
    {
      dirent = dir->readdir();
      continue;
    }

    if(Dir::isdir(rootDir + DIR_CHAR + dirent->d_name()) == true)
    {
      scanForIncludeDirectories(rootDir + DIR_CHAR + dirent->d_name());

      if(dirent->d_name() == "include")
      {
        includeDirectories.push_back(rootDir + DIR_CHAR + dirent->d_name());
      }
    }

    dirent = dir->readdir();
  }
}
