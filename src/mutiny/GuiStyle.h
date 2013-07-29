#ifndef MUTINY_ENGINE_GUI_STYLE_H
#define MUTINY_ENGINE_GUI_STYLE_H

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

private:
  std::shared_ptr<GuiStyleState> normal;
  std::shared_ptr<GuiStyleState> hover;
  std::shared_ptr<GuiStyleState> active;
  Font* font;

};

}

}

#endif

