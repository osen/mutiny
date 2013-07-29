#ifndef MUTINY_ENGINE_FONT_H
#define MUTINY_ENGINE_FONT_H

#include "Object.h"

#include <memory>
#include <vector>
#include <string>

namespace mutiny
{

namespace engine
{

class Texture2d;
class Resources;

class Font : public Object
{
  friend class mutiny::engine::Resources;

public:

private:
  static Font* load(std::string path);

  std::shared_ptr<Texture2d> texture;
  std::vector<std::string> characters;

};

}

}

#endif

