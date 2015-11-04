#include "CWrapper.h"

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

}

}

}

