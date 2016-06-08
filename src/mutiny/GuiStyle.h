#ifndef MUTINY_ENGINE_GUI_STYLE_H
#define MUTINY_ENGINE_GUI_STYLE_H

#include "RectOffset.h"
#include "ref.h"

#include <memory>

namespace mutiny
{

namespace engine
{

class GuiStyleState;
class Font;
class Gui;
class GuiStyle : public enable_ref
{
  friend class mutiny::engine::Gui;

public:
  GuiStyle();

  ref<GuiStyleState> getNormal();
  ref<GuiStyleState> getHover();
  ref<GuiStyleState> getActive();

  void setAlignment(int alignment);
  int getAlignment();

private:
  shared<GuiStyleState> normal;
  shared<GuiStyleState> hover;
  shared<GuiStyleState> active;
  ref<Font> font;
  RectOffset border;
  int alignment;

};

}

}

#endif

