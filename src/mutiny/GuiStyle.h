#ifndef MUTINY_ENGINE_GUI_STYLE_H
#define MUTINY_ENGINE_GUI_STYLE_H

#include "RectOffset.h"
#include "arc.h"

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

  arc<GuiStyleState> getNormal();
  arc<GuiStyleState> getHover();
  arc<GuiStyleState> getActive();

  void setAlignment(int alignment);
  int getAlignment();

private:
  arc<GuiStyleState> normal;
  arc<GuiStyleState> hover;
  arc<GuiStyleState> active;
  arc<Font> font;
  RectOffset border;
  int alignment;

};

}

}

#endif

