#include "CWrapper.h"
#include "../Exception.h"
#include "../Application.h"

namespace mutiny
{

namespace engine
{

namespace internal
{

PngData* PngData::create()
{
  PngData* rtn = Application::getGC()->gc_new<PngData>();

  return rtn;
}

PngData::~PngData()
{
  free(image);
}

GlBuffer* GlBuffer::create()
{
  GlBuffer* rtn = Application::getGC()->gc_new<GlBuffer>();

  return rtn;
}

GlBuffer::~GlBuffer()
{
  if(id != 0)
  {
    glDeleteBuffers(1, &id);
  }
}

#ifdef _WIN32
Win32FindData* Win32FindData::create()
{
  Win32FindData* rtn = Application::getGC()->gc_new<Win32FindData>();

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
  FindHandle* rtn = Application::getGC()->gc_new<FindHandle>();
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

