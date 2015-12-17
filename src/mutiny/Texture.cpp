#include "Texture.h"

namespace mutiny
{

namespace engine
{

Texture::Texture()
{

}

Texture::~Texture()
{

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
  return nativeTexture->getGLuint();
}

}

}

