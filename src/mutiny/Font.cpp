#include "Font.h"
#include "Texture2d.h"
#include "Debug.h"

#include <string>

namespace mutiny
{

namespace engine
{

Font* Font::load(std::string path)
{
  std::unique_ptr<Font> font(new Font());

  //Debug::log("Loading font from '" + path + "'");
  font->texture.reset(Texture2d::load(path));

  return font.release();
}

}

}

