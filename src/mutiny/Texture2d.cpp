#include "Texture2d.h"
#include "Color.h"
#include "Application.h"
#include "Mathf.h"
#include "Debug.h"

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_rotozoom.h>

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
    _nativeTexture.reset(&nativeTexture, std::bind(glDeleteTextures, 1, &nativeTexture));
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
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glBindTexture(GL_TEXTURE_2D, 0);
}

Texture2d* Texture2d::load(std::string path)
{
  SDL_Surface* tmpSurface = IMG_Load(std::string(path + ".png").c_str());

  if(tmpSurface == NULL)
  {
    //Debug::logError("Failed to load image '" + path + "'");
    throw std::exception();
  }

#ifdef EMSCRIPTEN
  SDL_Surface* surface = tmpSurface;
#else
  float targetX = Mathf::nextPowerOfTwo(tmpSurface->w);
  float targetY = Mathf::nextPowerOfTwo(tmpSurface->h);
  float scaleX = tmpSurface->w / targetX;
  float scaleY = tmpSurface->h / targetY;

  //std::cout << scaleX << " " << scaleY << std::endl;
  //std::cout << tmpSurface->w / scaleX << " " << tmpSurface->h / scaleY << std::endl;
  
  SDL_Surface* surface = zoomSurface(tmpSurface, scaleX, scaleY, SMOOTHING_ON);
  //SDL_Surface* surface = zoomSurface(tmpSurface, scaleX, scaleY, SMOOTHING_OFF);
#endif

  if(surface == NULL)
  {
    //Debug::logError("Failed to load image '" + path + "'");
    throw std::exception();
  }

  Texture2d* texture = new Texture2d(tmpSurface->w, tmpSurface->h);

  if(texture->nativeTexture == -1)
  {
    glGenTextures(1, &texture->nativeTexture);
    texture->_nativeTexture.reset(&texture->nativeTexture, std::bind(glDeleteTextures, 1, &texture->nativeTexture));
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

  //SDL_LockSurface(surface);

  glBindTexture(GL_TEXTURE_2D, texture->nativeTexture);
  glTexImage2D(GL_TEXTURE_2D, 0, noc, surface->w, surface->h, 0, fmt, GL_UNSIGNED_BYTE, surface->pixels);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glBindTexture(GL_TEXTURE_2D, 0);

  /*
  int val = 0;
  for(int y = 0; y < texture->height; y++)
  {
    for(int x = 0; x < texture->width; x++)
    {
      if(bpp == 3)
      {
        texture->setPixel(x, y, Color((int)((Uint8 *)surface->pixels)[val],
                             (int)((Uint8 *)surface->pixels)[val+1],
                             (int)((Uint8 *)surface->pixels)[val+2]));
      }
      else
      {
        texture->setPixel(x, y, Color((int)((Uint8 *)surface->pixels)[val],
                             (int)((Uint8 *)surface->pixels)[val+1],
                             (int)((Uint8 *)surface->pixels)[val+2],
                             (int)((Uint8 *)surface->pixels)[val+3]));

      }

      val+=bpp;
    }
  }
  */

  //SDL_UnlockSurface(surface);
  SDL_FreeSurface(surface);

  return texture;
}

}

}

