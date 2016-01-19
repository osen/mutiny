#include "Texture2d.h"
#include "Color.h"
#include "Application.h"
#include "Mathf.h"
#include "Debug.h"
#include "internal/CWrapper.h"

#include <memory>
#include <functional>
#include <vector>
#include <iostream>

namespace mutiny
{

namespace engine
{

arc<Texture2d> Texture2d::defaultTexture;

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

  if(y >= pixels.size() || x >= pixels.at(0).size())
  {
    return;
  }

  pixels.at(y).at(x) = color;
}

Color Texture2d::getPixel(int x, int y)
{
  return pixels.at(y).at(x);
}

void Texture2d::resize(int width, int height)
{
  this->width = width;
  this->height = height;

  while(pixels.size() < height)
  {
    pixels.push_back(std::vector<Color>(width));
  }

  for(int y = 0; y < height; y++)
  {
    while(pixels.at(y).size() < width)
    {
      pixels.at(y).push_back(Color(0, 0, 0, 0));
    }
  }
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

  if(nativeTexture.get() == NULL)
  {
    nativeTexture = gl::Uint::genTexture();
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

  glBindTexture(GL_TEXTURE_2D, nativeTexture->getGLuint());
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &imageBytes[0]);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
/*
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  if(glGenerateMipmap != NULL)
  {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);
  }
  else
  {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  }
*/

  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glBindTexture(GL_TEXTURE_2D, 0);
}

int poweroftwo(int input)
{
  input--;
  input |= input >> 1;
  input |= input >> 2;
  input |= input >> 4;
  input |= input >> 8;
  input |= input >> 16;
  input++;

  return input;
}

Texture2d* Texture2d::load(std::string path)
{
  arc<internal::PngData> image = internal::PngData::create();
  path = path + ".png";

  if(lodepng_decode32_file(&image->image, &image->width, &image->height, path.c_str()) != 0)
  {
    throw std::exception();
  }

  Texture2d* texture = new Texture2d(image->width, image->height);

  if(texture->nativeTexture.get() == NULL)
  {
    texture->nativeTexture = gl::Uint::genTexture();
  }

  int sampleWidth = image->width;
  int sampleHeight = image->height;

  sampleWidth = poweroftwo(image->width);
  sampleHeight = poweroftwo(image->height);

  std::cout << sampleWidth << " " << sampleHeight << std::endl;

  std::vector<GLbyte> imageBytes(sampleHeight * sampleWidth * 4);

  double scaleWidth =  (double)sampleWidth / (double)image->width;
  double scaleHeight = (double)sampleHeight / (double)image->height;

  for(int cy = 0; cy < sampleHeight; cy++)
  {
    for(int cx = 0; cx < sampleWidth; cx++)
    {
      int pixel = (cy * (sampleWidth * 4)) + (cx * 4);
      int nearestMatch =  (((int)(cy / scaleHeight) * (image->width * 4)) + ((int)(cx / scaleWidth) * 4) );
      imageBytes[pixel    ] =  image->image[nearestMatch    ];
      imageBytes[pixel + 1] =  image->image[nearestMatch + 1];
      imageBytes[pixel + 2] =  image->image[nearestMatch + 2];
      imageBytes[pixel + 3] =  image->image[nearestMatch + 3];
    }
  }

  glBindTexture(GL_TEXTURE_2D, texture->nativeTexture->getGLuint());
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sampleWidth, sampleHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, &imageBytes[0]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  //glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
  //glGenerateMipmap(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, 0);

  return texture;
}

}

}

