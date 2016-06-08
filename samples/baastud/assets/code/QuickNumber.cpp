#include "QuickNumber.h"

#include <sstream>

using namespace mutiny::engine;

QuickNumber::QuickNumber()
{
  fontTexture = Resources::load<Texture2d>("fonts/score");
  wFontTexture = Resources::load<Texture2d>("fonts/score_w");
}

void QuickNumber::drawW(int number, int x, int y)
{
  std::stringstream ss;
  std::string num;

  int charWidth = (float)wFontTexture->getWidth() / 10.0f;
  float point = 1.0f / 10.0f;

  ss << number;
  num = ss.str();

  for(int i = 0; i < num.length(); i++)
  {
    std::string cs = "";
    cs += num[i];
    float nc = atoi(cs.c_str());

    Gui::drawTextureWithTexCoords(Rect(x + i * charWidth, y, charWidth, wFontTexture->getHeight()),
      wFontTexture.get(), Rect(point * nc, 0, (point * nc) + point, 1));
  }
}

void QuickNumber::draw(int number, int x, int y)
{
  std::stringstream ss;
  std::string num;
  int charWidth = (float)fontTexture->getWidth() / 10.0f;
  float point = 1.0f / 10.0f;

  ss << number;
  num = ss.str();

  for(int i = 0; i < num.length(); i++)
  {
    std::string cs = "";
    cs += num[i];
    float nc = atoi(cs.c_str());

    Gui::drawTextureWithTexCoords(Rect(x + i * charWidth, y, charWidth, fontTexture->getHeight()),  
      fontTexture.get(), Rect(point * nc, 0, (point * nc) + point, 1));
  }
}
