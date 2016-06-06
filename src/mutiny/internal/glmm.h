#ifndef GLMM_H
#define GLMM_H

#include "../ref.h"

#include <GL/glew.h>

namespace gl
{

class Uint : public enable_ref
{
public:
  static shared<Uint> genBuffer();
  static shared<Uint> genTexture();
  static shared<Uint> genFramebuffer();
  static shared<Uint> genRenderbuffer();
  static shared<Uint> createVertexShader();
  static shared<Uint> createFragmentShader();
  static shared<Uint> createProgram();

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

