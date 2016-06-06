#include "glmm.h"
#include "../Application.h"
#include "../Exception.h"

namespace gl
{

shared<Uint> Uint::createProgram()
{
  shared<Uint> rtn(new Uint());

  rtn->uint = glCreateProgram();

  if(rtn->uint == 0)
  {
    throw mutiny::engine::Exception("Failed to allocate shader program");
  }

  rtn->type = PROGRAM;

  return rtn;
}

shared<Uint> Uint::createVertexShader()
{
  shared<Uint> rtn(new Uint());

  rtn->uint = glCreateShader(GL_VERTEX_SHADER);

  if(rtn->uint == 0)
  {
    throw mutiny::engine::Exception("Failed to allocate vertex shader");
  }

  rtn->type = VERTEXSHADER;

  return rtn;
}

shared<Uint> Uint::createFragmentShader()
{
  shared<Uint> rtn(new Uint());

  rtn->uint = glCreateShader(GL_FRAGMENT_SHADER);

  if(rtn->uint == 0)
  {
    throw mutiny::engine::Exception("Failed to allocate fragment shader");
  }

  rtn->type = FRAGMENTSHADER;

  return rtn;
}

shared<Uint> Uint::genBuffer()
{
  shared<Uint> rtn(new Uint());

  glGenBuffers(1, &rtn->uint);

  if(rtn->uint == 0)
  {
    throw mutiny::engine::Exception("Failed to allocate buffer");
  }

  rtn->type = BUFFER;

  return rtn;
}

shared<Uint> Uint::genTexture()
{
  shared<Uint> rtn(new Uint());

  glGenTextures(1, &rtn->uint);

  if(rtn->uint == 0)
  {
    throw mutiny::engine::Exception("Failed to allocate texture");
  }

  rtn->type = TEXTURE;

  return rtn;
}

shared<Uint> Uint::genFramebuffer()
{
  shared<Uint> rtn(new Uint());

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

shared<Uint> Uint::genRenderbuffer()
{
  shared<Uint> rtn(new Uint());

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

  if(type == BUFFER)
  {
    glDeleteBuffers(1, &uint);
  }
  else if(type == TEXTURE)
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
  else if(type == VERTEXSHADER || type == FRAGMENTSHADER)
  {
    glDeleteShader(uint);
  }
  else if(type == PROGRAM)
  {
    glDeleteProgram(uint);
  }
}

}
