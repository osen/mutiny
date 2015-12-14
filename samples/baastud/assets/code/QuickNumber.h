#ifndef QUICKNUMBER_H
#define QUICKNUMBER_H

#include <mutiny/mutiny.h>

#include <string>

using namespace mutiny::engine;

class QuickNumber
{
public:
  QuickNumber();

  void draw(int number, int x, int y);
  void drawW(int number, int x, int y);

private:
  arc<Texture2d> fontTexture;
  arc<Texture2d> wFontTexture;

};

#endif
