#include "glmm.h"

namespace gl
{

arc<Uint> Uint::genTexture()
{
  arc<Uint> rtn = arc<Uint>::alloc();

  glGenTextures(1, &rtn->uint);

  if(rtn->uint == 0)
  {
    throw std::exception();
  }

  rtn->type = TEXTURE;

  return rtn;
}

arc<Uint> Uint::genFramebuffer()
{
  arc<Uint> rtn = arc<Uint>::alloc();

  glGenFramebuffers(1, &rtn->uint);

  if(rtn->uint == 0)
  {
    throw std::exception();
  }

  rtn->type = FRAMEBUFFER;

  return rtn;
}

arc<Uint> Uint::genRenderbuffer()
{
  arc<Uint> rtn = arc<Uint>::alloc();

  glGenRenderbuffers(1, &rtn->uint);

  if(rtn->uint == 0)
  {
    throw std::exception();
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