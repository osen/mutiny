#include "CWrapper.h"
#include "../Exception.h"

namespace mutiny
{

namespace engine
{

namespace internal
{

std::shared_ptr<PngData> PngData::create()
{
  static PngData s;
  std::shared_ptr<PngData> rtn(new PngData(s));

  return rtn;
}

PngData::~PngData()
{
  free(image);
}

std::shared_ptr<GlBuffer> GlBuffer::create()
{
  static GlBuffer s;
  std::shared_ptr<GlBuffer> rtn(new GlBuffer(s));

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
std::shared_ptr<Win32FindData> Win32FindData::create()
{
  static Win32FindData s;
  std::shared_ptr<Win32FindData> rtn(new Win32FindData(s));

  return rtn;
}

FindHandle::~FindHandle()
{
  if(hFind != INVALID_HANDLE_VALUE)
  {
    FindClose(hFind);
  }
}

std::shared_ptr<FindHandle> FindHandle::FindFirstFile(std::string path, std::shared_ptr<Win32FindData> findData)
{
  static FindHandle s;
  std::shared_ptr<FindHandle> rtn(new FindHandle(s));
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

