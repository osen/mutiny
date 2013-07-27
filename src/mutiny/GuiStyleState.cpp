#include "GuiStyleState.h"
#include "Color.h"
#include "Texture2d.h"

#include <functional>

namespace mutiny
{

namespace engine
{

GuiStyleState::GuiStyleState()
{
  Texture2d* tex = new Texture2d(1, 1);
  background.reset(tex);
  tex->setPixel(0, 0, Color(0, 0, 1, 1));
  tex->apply();
}

void GuiStyleState::setBackground(Texture2d* background)
{
  /*
  Texture2d* tex = new Texture2d(background->getWidth(), background->getHeight());

  for(int y = 0; y < background->getHeight(); y++)
  {
    for(int x = 0; x < background->getWidth(); x++)
    {
      tex->setPixel(x, y, background->getPixel(x, y));
    }
  }

  tex->apply();
  this->background.reset(tex);
  */

  this->background.reset(background, std::bind(dummyDeleter));
}

Texture2d* GuiStyleState::getBackground()
{
  return background.get();
}

void GuiStyleState::dummyDeleter()
{

}

}

}

