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

  std::ifstream file(path + ".font");

  if(file.is_open() == false)
  {
    Debug::logError("Failed to open font");
    throw std::exception();
  }

  std::vector<std::string> characters;
  int maxChars = 0;

  while(file.eof() == false)
  {
    std::string line;
    getline(file, line);

    if(line.length() < 1)
    {
      break;
    }

    if(line.length() > maxChars)
    {
      maxChars = line.length();
    }

    characters.push_back(line);
  }

  Vector2 charSize((float)font->texture->getWidth() / (float)maxChars, (float)font->texture->getHeight() / (float)characters.size());

  //std::cout << charSize.x << " " << charSize.y << std::endl;

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

