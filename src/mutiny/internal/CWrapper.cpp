#include "CWrapper.h"
#include "../Exception.h"

namespace mutiny
{

namespace engine
{

namespace internal
{

arc<PngData> PngData::create()
{
  arc<PngData> rtn = arc<PngData>::alloc();

  return rtn;
}

PngData::~PngData()
{
  free(image);
}

arc<GlBuffer> GlBuffer::create()
{
  arc<GlBuffer> rtn = arc<GlBuffer>::alloc();

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
arc<Win32FindData> Win32FindData::create()
{
  arc<Win32FindData> rtn = arc<Win32FindData>::alloc();

  return rtn;
}

FindHandle::~FindHandle()
{
  if(hFind != INVALID_HANDLE_VALUE)
  {
    FindClose(hFind);
  }
}

arc<FindHandle> FindHandle::FindFirstFile(std::string path, arc<Win32FindData> findData)
{
  arc<FindHandle> rtn = arc<FindHandle>::alloc();
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

