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
  static Uint* createVertexShader();
  static Uint* createFragmentShader();
  static Uint* createProgram();

  ~Uint();

  GLuint getGLuint();

private:
  static const int BUFFER = 0;
  static const int TEXTURE = 1;
  static const int FRAMEBUFFER = 2;
  static const int RENDERBUFFER = 3;
  static const int VERTEXSHADER = 4;
  static const int FRAGMENTSHADER = 5;
  static const int PROGRAM = 6;

  GLuint uint;
  int type;

};

}

#endif

