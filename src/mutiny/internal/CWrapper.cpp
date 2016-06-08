#include "CWrapper.h"
#include "../Exception.h"
#include "../Application.h"

#include <cstdlib>

namespace mutiny
{

namespace engine
{

namespace internal
{

shared<PngData> PngData::create()
{
  shared<PngData> rtn(new PngData());
  rtn->image = NULL;
  rtn->width = 0;
  rtn->height = 0;

  return rtn;
}

PngData::~PngData()
{
  free(image);
}

#ifdef _WIN32
Win32FindData* Win32FindData::create()
{
  Win32FindData* rtn = new Win32FindData();

  return rtn;
}

FindHandle::~FindHandle()
{
  if(hFind != INVALID_HANDLE_VALUE)
  {
    FindClose(hFind);
  }
}

FindHandle* FindHandle::FindFirstFile(std::string path, Win32FindData* findData)
{
  FindHandle* rtn = new FindHandle();
  rtn->hFind = INVALID_HANDLE_VALUE;
  rtn->findData = findData;
  rtn->hFind = ::FindFirstFile(path.c_str(), &rtn->findData->ffd);

  if(rtn->hFind == INVALID_HANDLE_VALUE)
  {
    throw Exception("Failed to open directory");
  }

  return rtn;
}

bool FindHandle::FindNextFile()
{
  return ::FindNextFile(hFind, &findData->ffd);
}
#endif

}

}

}

