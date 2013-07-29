#include "Font.h"
#include "Debug.h"

#include <string>

namespace mutiny
{

namespace engine
{

Font* Font::load(std::string path)
{
  Font* font = new Font();

  Debug::log("Loading font from '" + path + "'");

  return font;
}

}

}

