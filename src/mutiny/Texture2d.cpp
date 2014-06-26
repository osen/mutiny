#include "Texture2d.h"
#include "Color.h"
#include "Application.h"
#include "Mathf.h"
#include "Debug.h"
#include "internal/pngwrapper.h"

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#ifdef WINDOWS
#else
#include <SDL/SDL_rotozoom.h>
#endif

#include <memory>
#include <functional>
#include <vector>
#include <iostream>

namespace mutiny
{

namespace engine
{

Texture2d::Texture2d(int width, int height)
{
  this->width = width;
  this->height = height;
}

Texture2d::~Texture2d()
{

}

void Texture2d::setPixel(int x, int y, Color color)
{
  if(pixels.size() < 1)
  {
    populateSpace();
  }

  pixels[y][x] = color;
}

Color Texture2d::getPixel(int x, int y)
{
  return pixels[y][x];
}

void Texture2d::populateSpace()
{
  for(int y = 0; y < height; y++)
  {
    pixels.push_back(std::vector<Color>(width));
  }
}

void Texture2d::apply()
{
  std::vector<GLbyte> imageBytes;

  if(nativeTexture == -1)
  {
    glGenTextures(1, &nativeTexture);
    _nativeTexture.reset(&nativeTexture, std::bind(deleteTexture, nativeTexture));
  }

  if(pixels.size() < 1)
  {
    populateSpace();
  }

  for(int y = 0; y < height; y++)
  {
    for(int x = 0; x < width; x++)
    {
      imageBytes.push_back(pixels[y][x].r * 255.0f);
      imageBytes.push_back(pixels[y][x].g * 255.0f);
      imageBytes.push_back(pixels[y][x].b * 255.0f);
      imageBytes.push_back(pixels[y][x].a * 255.0f);
    }
  }

  glBindTexture(GL_TEXTURE_2D, nativeTexture);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &imageBytes[0]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glGenerateMipmap(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, 0);
}

Texture2d* Texture2d::load(std::string path)
{
#ifdef USE_LIBPNG
  int pngId; std::shared_ptr<void> _pngId;

  pngId = pngwrapper_load(path + ".png");

  if(pngId == 0)
  {
    throw std::exception();
  }

  _pngId.reset(&pngId, std::bind(pngwrapper_unload, pngId));

  Texture2d* texture = new Texture2d(pngwrapper_width(pngId), pngwrapper_height(pngId));

  if(texture->nativeTexture == -1)
  {
    glGenTextures(1, &texture->nativeTexture);
    texture->_nativeTexture.reset(&texture->nativeTexture, std::bind(deleteTexture, texture->nativeTexture));
  }

  glBindTexture(GL_TEXTURE_2D, texture->nativeTexture);
  pngwrapper_texture(pngId);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  //glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
  glGenerateMipmap(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, 0);

  return texture;
#else
  std::shared_ptr<SDL_Surface> tmpSurface;
  std::shared_ptr<SDL_Surface> surface;

  tmpSurface.reset(IMG_Load(std::string(path + ".png").c_str()), std::bind(SDL_FreeSurface, std::placeholders::_1));

  if(tmpSurface.get() == NULL)
  {
    //Debug::logError("Failed to load image '" + path + "'");
    throw std::exception();
  }

//#if defined EMSCRIPTEN || defined WINDOWS
  surface = tmpSurface;
//#else
//  float targetX = Mathf::nextPowerOfTwo(tmpSurface->w);
//  float targetY = Mathf::nextPowerOfTwo(tmpSurface->h);
//  float scaleX = tmpSurface->w / targetX;
//  float scaleY = tmpSurface->h / targetY;
//
//  //std::cout << scaleX << " " << scaleY << std::endl;
//  //std::cout << tmpSurface->w / scaleX << " " << tmpSurface->h / scaleY << std::endl;
//  
//  surface.reset(zoomSurface(tmpSurface.get(), scaleX, scaleY, SMOOTHING_ON), std::bind(SDL_FreeSurface, std::placeholders::_1));
//#endif

  if(surface.get() == NULL)
  {
    //Debug::logError("Failed to load image '" + path + "'");
    throw std::exception();
  }

  Texture2d* texture = new Texture2d(tmpSurface->w, tmpSurface->h);

  if(texture->nativeTexture == -1)
  {
    glGenTextures(1, &texture->nativeTexture);
    texture->_nativeTexture.reset(&texture->nativeTexture, std::bind(deleteTexture, texture->nativeTexture));
  }

  GLint bpp = surface->format->BytesPerPixel;
  GLint noc = 0;
  GLint fmt = 0;

  if(bpp == 4)
  {
    noc = GL_RGBA;

    if (surface->format->Rmask == 0x000000ff)
    {
      fmt = GL_RGBA;
    }
    else
    {
      fmt = GL_BGRA;
    }
  }
  else if(bpp == 3)
  {
    noc = GL_RGB;

    if(surface->format->Rmask == 0x000000ff)
    {
      fmt = GL_RGB;
    }
    else
    {
      fmt = GL_BGR;
    }
  }
  else
  {
    Debug::logError("Invalid texture format");
    throw std::exception();
  }

  glBindTexture(GL_TEXTURE_2D, texture->nativeTexture);
  glTexImage2D(GL_TEXTURE_2D, 0, noc, surface->w, surface->h, 0, fmt, GL_UNSIGNED_BYTE, surface->pixels);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  glGenerateMipmap(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, 0);

  return texture;
#endif
}

}

}

