#include "Font.h"
#include "Texture2d.h"
#include "CharacterInfo.h"
#include "Vector2.h"
#include "Debug.h"

#include <string>
#include <fstream>
#include <iostream>

namespace mutiny
{

namespace engine
{

Font* Font::load(std::string path)
{
  std::unique_ptr<Font> font(new Font());

  //Debug::log("Loading font from '" + path + "'");
  font->texture.reset(Texture2d::load(path));

  std::vector<std::string> characters;
  int maxChars = 0;
  std::string chars;

  for(int i = 32; i < 127; i++)
  {
    chars += (char)i;
  }

  maxChars = chars.length();
  characters.push_back(chars);

  Vector2 charSize((float)font->texture->getWidth() / (float)maxChars, (float)font->texture->getHeight() / (float)characters.size());

  for(int y = 0; y < characters.size(); y++)
  {
    for(int x = 0; x < characters[y].length(); x++)
    {
      CharacterInfo info;
      info.index = characters[y][x];
      info.vert = Rect(0, 0, charSize.x, charSize.y);
      info.uv.x = ((float)x * charSize.x) / (float)font->texture->getWidth();
      info.uv.y = ((float)y * charSize.y) / (float)font->texture->getHeight();
      info.uv.width = ((float)x * charSize.x + charSize.x) / (float)font->texture->getWidth();
      info.uv.height = ((float)y * charSize.y + charSize.y) / (float)font->texture->getHeight();
      font->characterInfo.push_back(info);
    }
  }

  return font.release();
}

bool Font::getCharacterInfo(char character, CharacterInfo* characterInfo)
{
  for(int i = 0; i < this->characterInfo.size(); i++)
  {
    if(this->characterInfo.at(i).index == character)
    {
      *characterInfo = this->characterInfo.at(i);
      return true;
    }
  }

  return false;
}

}

}

