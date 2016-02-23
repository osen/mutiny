#include "glmm.h"
#include "../Application.h"
#include "../Exception.h"

namespace gl
{

Uint* Uint::genTexture()
{
  Uint* rtn = mutiny::engine::Application::getGC()->gc_new<Uint>();

  glGenTextures(1, &rtn->uint);

  if(rtn->uint == 0)
  {
    throw mutiny::engine::Exception("Failed to allocate texture");
  }

  rtn->type = TEXTURE;

  return rtn;
}

Uint* Uint::genFramebuffer()
{
  Uint* rtn = mutiny::engine::Application::getGC()->gc_new<Uint>();

  if(glGenFramebuffers == NULL)
  {
    throw mutiny::engine::Exception("Frame buffers not supported by system");
  }

  glGenFramebuffers(1, &rtn->uint);

  if(rtn->uint == 0)
  {
    throw mutiny::engine::Exception("Failed to allocate frame buffer");
  }

  rtn->type = FRAMEBUFFER;

  return rtn;
}

Uint* Uint::genRenderbuffer()
{
  Uint* rtn = mutiny::engine::Application::getGC()->gc_new<Uint>();

  glGenRenderbuffers(1, &rtn->uint);

  if(rtn->uint == 0)
  {
    throw mutiny::engine::Exception("Failed to allocate render buffer");
  }

  rtn->type = RENDERBUFFER;

  return rtn;
}

GLuint Uint::getGLuint()
{
  return uint;
}

Uint::~Uint()
{
  if(uint == 0) return;

  if(type == TEXTURE)
  {
    glDeleteTextures(1, &uint);
  }
  else if(type == FRAMEBUFFER)
  {
    glDeleteFramebuffers(1, &uint);
  }
  else if(type == RENDERBUFFER)
  {
    glDeleteRenderbuffers(1, &uint);
  }
}

}