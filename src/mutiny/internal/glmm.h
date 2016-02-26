#ifndef GLMM_H
#define GLMM_H

#include <GL/glew.h>

namespace gl
{

class Uint
{
public:
  static Uint* genBuffer();
  static Uint* genTexture();
  static Uint* genFramebuffer();
  static Uint* genRenderbuffer();

  ~Uint();

  GLuint getGLuint();

private:
  static const int BUFFER = 0;
  static const int TEXTURE = 1;
  static const int FRAMEBUFFER = 2;
  static const int RENDERBUFFER = 3;

  GLuint uint;
  int type;

};

}

#endif

