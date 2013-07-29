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

    if(line.length() > maxChars)
    {
      maxChars = line.length();
    }

    characters.push_back(line);
  }

  Vector2 charSize(font->texture->getWidth() / (float)maxChars, font->texture->getHeight() / (float)characters.size());

  //std::cout << charSize.x << " " << charSize.y << std::endl;

  for(int y = 0; y < characters.size(); y++)
  {
    for(int x = 0; x < characters[y].length(); x++)
    {
      CharacterInfo info;
      info.index = characters[y][x];
      info.uv.x = ((float)x * charSize.x) / (float)font->texture->getWidth();
      info.uv.width = ((float)x * charSize.x + charSize.x) / (float)font->texture->getWidth();
      info.uv.y = ((float)y * charSize.y) / (float)font->texture->getWidth();
      info.uv.height = ((float)y * charSize.y + charSize.y) / (float)font->texture->getWidth();
      //std::cout << "X: " << info.uv.x << " Y: " << info.uv.y << std::endl;
      //Debug::log(std::string("") + characters[y][x]);
      font->characterInfo.push_back(info);
    }
  }

  return font.release();
}

}

}

