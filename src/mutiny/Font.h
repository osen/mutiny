#ifndef MUTINY_ENGINE_FONT_H
#define MUTINY_ENGINE_FONT_H

#include "Object.h"
#include "CharacterInfo.h"

#include <memory>
#include <vector>
#include <string>

namespace mutiny
{

namespace engine
{

class Texture2d;
class Resources;
class Gui;

class Font : public Object
{
  friend class mutiny::engine::Resources;
  friend class mutiny::engine::Gui;

public:
  bool getCharacterInfo(char character, CharacterInfo& characterInfo);

private:
  static ref<Font> load(std::string path);

  shared<Texture2d> texture;
  std::vector<CharacterInfo> characterInfo;

};

}

}

#endif

