#include "Texture.h"

namespace mutiny
{

namespace engine
{

Texture::Texture()
{
  nativeTexture = -1;
}

Texture::~Texture()
{

}

void Texture::deleteFramebuffer(GLuint id)
{
  glDeleteFramebuffers(1, &id);
}

void Texture::deleteTexture(GLuint id)
{
  glDeleteTextures(1, &id);
}

void Texture::deleteRenderbuffer(GLuint id)
{
  glDeleteRenderbuffers(1, &id);
}

int Texture::getWidth()
{
  return width;
}

int Texture::getHeight()
{
  return height;
}

GLuint Texture::getNativeTexture()
{
  return nativeTexture;
}

}

}

