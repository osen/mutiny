#ifndef MUTINY_ENGINE_GUI_STYLE_H
#define MUTINY_ENGINE_GUI_STYLE_H

#include "RectOffset.h"

#include <memory>

namespace mutiny
{

namespace engine
{

class GuiStyleState;
class Font;
class Gui;
class GuiStyle
{
  friend class mutiny::engine::Gui;

public:
  GuiStyle();

  GuiStyleState* getNormal();
  GuiStyleState* getHover();
  GuiStyleState* getActive();

  void setAlignment(int alignment);
  int getAlignment();

private:
  GuiStyleState* normal;
  GuiStyleState* hover;
  GuiStyleState* active;
  Font* font;
  RectOffset border;
  int alignment;

};

}

}

#endif

