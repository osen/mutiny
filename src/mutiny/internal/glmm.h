#ifndef GLMM_H
#define GLMM_H

#include "../arc.h"

#include <GL/glew.h>

namespace gl
{

class Uint
{
public:
  static arc<Uint> genTexture();
  static arc<Uint> genFramebuffer();
  static arc<Uint> genRenderbuffer();

  ~Uint();

  GLuint getGLuint();

private:
  static const int TEXTURE = 0;
  static const int FRAMEBUFFER = 1;
  static const int RENDERBUFFER = 2;

  GLuint uint;
  int type;

};

}

#endif

