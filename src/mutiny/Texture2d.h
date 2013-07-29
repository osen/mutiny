#ifndef MUTINY_ENGINE_TEXTURE2D_H
#define MUTINY_ENGINE_TEXTURE2D_H

#include "Texture.h"

#include <vector>

namespace mutiny
{

namespace engine
{

class Color;
class Resources;
class Font;

class Texture2d : public Texture
{
  friend class Resources;
  friend class Font;

public:
  Texture2d(int width, int height);
  virtual ~Texture2d();
  void setPixel(int x, int y, Color color);
  Color getPixel(int x, int y);
  void apply();

private:
  static Texture2d* load(std::string path);
  static int nearestPowerOfTwo(int size);

  std::vector<std::vector<Color> > pixels;

  void populateSpace();

};

}

}

#endif

