#include "FsSync.h"
#include "features.h"

#ifdef HAS_DIRENT
  #include <dirent.h>
  #include <unistd.h>
  #include <sys/stat.h>
#endif

#ifdef HAS_WINAPI
  #include <windows.h>
#endif

#include <iostream>
#include <fstream>
#include <cstring>

struct FsCommand
{
  int command;
  std::string path;
};

#ifdef HAS_WINAPI
BOOL DirectoryExists(LPCTSTR szPath)
{
  DWORD dwAttrib = GetFileAttributes(szPath);

  return (dwAttrib != INVALID_FILE_ATTRIBUTES && 
         (dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}
#endif

struct Directory
{
  static bool exists(std::string path)
  {
#ifdef HAS_DIRENT
    DIR *dir;

    dir = opendir(path.c_str());

    if(!dir)
    {
      return false;
    }

    closedir(dir);

    return true;
#endif
#ifdef HAS_WINAPI
    return DirectoryExists(path.c_str());
#endif
  }

  static void mkdir(std::string path)
  {
#ifdef HAS_DIRENT
    ::mkdir(path.c_str(), 0700);
#endif
#ifdef HAS_WINAPI
    CreateDirectory (path.c_str(), NULL);
#endif
  }

  static void remove(std::string path)
  {
    ::remove(path.c_str());
  }

  static void list(std::string path, std::vector<std::string>& rtn)
  {
#ifdef HAS_DIRENT
    DIR *dir;
    dirent *ep;

    dir = opendir(path.c_str());

    if(!dir)
    {
      return;
    }

    while(ep = readdir(dir))
    {
      if(strcmp(".", ep->d_name) != 0 &&
         strcmp("..", ep->d_name))
      {
        rtn.push_back(ep->d_name);
      }
    }

    closedir(dir);
#endif
#ifdef HAS_WINAPI
    WIN32_FIND_DATA fdFile;
    HANDLE hFind;
    char sPath[MAX_PATH];

    sprintf(sPath, "%s\\*.*", path.c_str());

    if((hFind = FindFirstFile(sPath, &fdFile)) == INVALID_HANDLE_VALUE)
    {
      return;
    }

    do
    {
      if(strcmp(".", fdFile.cFileName) != 0 &&
         strcmp("..", fdFile.cFileName))
      {
        rtn.push_back(fdFile.cFileName);
      }
    }
    while(FindNextFile(hFind, &fdFile));
#endif
  }
};

struct File
{
  static bool exists(std::string path)
  {
    FILE *file;

    if(Directory::exists(path))
    {
      return false;
    }

    file = fopen(path.c_str(), "r");

    if(!file)
    {
      return false;
    }

    fclose(file);

    return true;
  }

  static time_t modified(std::string path)
  {
    struct stat st;

    stat(path.c_str(), &st);

    return st.st_mtime;
  }

  static void remove(std::string path)
  {
    ::remove(path.c_str());
  }

  static void copy(std::string destination, std::string source)
  {
    std::ifstream src(source.c_str(), std::ios::binary);
    std::ofstream dest(destination.c_str(), std::ios::binary);

    dest << src.rdbuf();

    src.close();
    dest.close();
  }
};

void FsSync::removeOrphanedFiles(std::string destination, std::string path,
  std::vector<std::string>& sources)
{
  std::vector<std::string> files;
  std::string splitter;

  if(path != "")
  {
    splitter = "/";
  }

  Directory::list(destination + splitter + path, files);

  for(size_t i = 0; i < files.size(); i++)
  {
    bool exists = false;

    if(Directory::exists(destination + splitter + path + "/" + files.at(i)))
    {
      removeOrphanedFiles(destination, path + splitter + files.at(i), sources);
      continue;
    }

    for(size_t j = 0; j < sources.size(); j++)
    {
      if(File::exists(sources.at(j) + splitter + path + "/"
        + files.at(i)) == true)
      {
        exists = true;
      }
    }

    if(!exists)
    {
      std::cout << "Deleting: " << destination << splitter << path
        << "/" << files.at(i) << std::endl;

      File::remove(destination + splitter + path + "/" + files.at(i));
    }
  }
}

void FsSync::removeOrphanedDirectories(std::string destination,
  std::string path, std::vector<std::string>& sources)
{
  std::vector<std::string> files;
  std::string splitter;

  if(path != "")
  {
    splitter = "/";
  }

  Directory::list(destination + splitter + path, files);

  for(size_t i = 0; i < files.size(); i++)
  {
    bool exists = false;

    if(File::exists(destination + splitter + path + "/" + files.at(i)))
    {
      continue;
    }

    removeOrphanedDirectories(destination, path + splitter + files.at(i),
      sources);

    for(size_t j = 0; j < sources.size(); j++)
    {
      if(Directory::exists(sources.at(j) + splitter + path + "/"
        + files.at(i)) == true)
      {
        exists = true;
      }
    }

    if(!exists)
    {
      std::cout << "Deleting: " << destination << splitter << path
        << "/" << files.at(i) << std::endl;

      Directory::remove(destination + splitter + path + "/" + files.at(i));
    }
  }
}

void FsSync::copyRequiredFiles(std::string destination,
  std::string path, std::vector<std::string>& sources)
{
  std::vector<std::string> files;
  std::string splitter;

  if(path != "")
  {
    splitter = "/";
  }

  for(size_t j = 0; j < sources.size(); j++)
  {
    std::vector<std::string> files;

    Directory::list(sources.at(j) + splitter + path, files);

    for(size_t i = 0; i < files.size(); i++)
    {
      bool exists = false;

      if(Directory::exists(sources.at(j) + splitter + path + "/" + files.at(i)))
      {
        copyRequiredFiles(destination, path + splitter + files.at(i),
          sources);

        continue;
      }

      if(!File::exists(destination + splitter + path + "/" + files.at(i)) ||
        File::modified(sources.at(j) + splitter + path + "/" + files.at(i)) >
        File::modified(destination + splitter + path + "/" + files.at(i)))
      {
        std::cout << "Copying file: " << sources.at(j) << splitter
          << path << "/" << files.at(i) << std::endl;

        File::copy(
          destination + splitter + path + "/" + files.at(i),
          sources.at(j) + splitter + path + "/" + files.at(i));
      }
    }
  }
}

void FsSync::createMissingDirectories(std::string destination,
  std::string path, std::vector<std::string>& sources)
{
  std::vector<std::string> files;
  std::string splitter;

  if(path != "")
  {
    splitter = "/";
  }

  for(size_t j = 0; j < sources.size(); j++)
  {
    std::vector<std::string> files;

    Directory::list(sources.at(j) + splitter + path, files);

    for(size_t i = 0; i < files.size(); i++)
    {
      bool exists = false;

      if(File::exists(sources.at(j) + splitter + path + "/" + files.at(i)))
      {
        continue;
      }

      if(!Directory::exists(destination + splitter + path + "/" + files.at(i)))
      {
        std::cout << "Creating directory: " << destination << splitter
          << path << "/" << files.at(i) << std::endl;

        Directory::mkdir(destination + splitter + path + "/" + files.at(i));
      }

      createMissingDirectories(destination, path + splitter + files.at(i),
        sources);
    }
  }
}

void FsSync::sync(std::string destination, std::vector<std::string>& sources)
{
  if(Directory::exists(destination))
  {
    std::cout << "Destination folder exists; cleaning" << std::endl;
    std::cout << "Removing orphaned files" << std::endl;
    removeOrphanedFiles(destination, "", sources);
    std::cout << "Removing orphaned directories" << std::endl;
    removeOrphanedDirectories(destination, "", sources);
  }
  else
  {
    std::cout << "Making directory: " << destination << std::endl;
    Directory::mkdir(destination);
  }

  std::cout << "Creating missing directories" << std::endl;
  createMissingDirectories(destination, "", sources);

  std::cout << "Copying required files" << std::endl;
  copyRequiredFiles(destination, "", sources);
}
