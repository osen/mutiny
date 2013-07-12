#include "Texture2d.h"
#include "Color.h"
#include "Application.h"
#include "Debug.h"

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
//#include <SDL/SDL_rotozoom.h>

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

int Texture2d::nearestPowerOfTwo(int size)
{
  if(size != 0)
  {
    size--;
    size |= (size >> 1);  //Or first 2 bits
    size |= (size >> 2);  //Or next 2 bits
    size |= (size >> 4);  //Or next 4 bits
    size |= (size >> 8);  //Or next 8 bits
    size |= (size >> 16); //Or next 16 bits
    size++;
  }

  return size;
}

void Texture2d::setPixel(int x, int y, Color color)
{
  if(pixels.size() < 1)
  {
    populateSpace();
  }

  pixels[y][x] = color;
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
  //SDL_Surface* surfaceO = SDL_CreateRGBSurface(SDL_SWSURFACE | SDL_SRCALPHA, nearestPowerOfTwo(tmpSurface->w), nearestPowerOfTwo(tmpSurface->h), tmpSurface->format->BytesPerPixel, tmpSurface->format->Rmask, tmpSurface->format->Gmask, tmpSurface->format->Bmask, tmpSurface->format->Amask);
  //SDL_Surface* surfaceO = SDL_CreateRGBSurface(SDL_SWSURFACE, tmpSurface->w, tmpSurface->h, 24, tmpSurface->format->Rmask, tmpSurface->format->Gmask, tmpSurface->format->Bmask, tmpSurface->format->Amask);
  //SDL_Rect rect = { 10, 10, 10, 10 };
  //SDL_SetAlpha(tmpSurface, 0, 0);
  //SDL_BlitSurface(tmpSurface, 0, surfaceO, 0);
  //SDL_Surface* surfaceA = zoomSurface(tmpSurface, 1, 1, false);
  //SDL_Surface* surfaceC = SDL_ConvertSurface(tmpSurface, tmpSurface->format, tmpSurface->flags);
  //SDL_Surface* surfaceB = SDL_DisplayFormatAlpha(tmpSurface);
  SDL_Surface* surface = tmpSurface;
  //SDL_Surface* surface = surfaceO;

  if(surface == NULL)
  {
    //Debug::logError("Failed to load image '" + path + "'");
    throw std::exception();
  }

  Texture2d* texture = new Texture2d(surface->w, surface->h);

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
  glTexImage2D(GL_TEXTURE_2D, 0, noc, texture->width, texture->height, 0, fmt, GL_UNSIGNED_BYTE, surface->pixels);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glBindTexture(GL_TEXTURE_2D, 0);

  //SDL_UnlockSurface(surface);
  SDL_FreeSurface(surface);

  return texture;
}

}

}

