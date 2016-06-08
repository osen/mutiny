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
class Application;
class MeshRenderer;

class Texture2d : public Texture
{
  friend class Resources;
  friend class Font;
  friend class Application;
  friend class MeshRenderer;

public:
  static shared<Texture2d> create(int width, int height);
  Texture2d();
  Texture2d(int width, int height);
  virtual ~Texture2d();
  void resize(int width, int height);
  void setPixel(int x, int y, Color color);
  Color getPixel(int x, int y);
  void apply();

private:
  static ref<Texture2d> load(std::string path);

  std::vector<std::vector<Color> > pixels;

  void populateSpace();

};

}

}

#endif

