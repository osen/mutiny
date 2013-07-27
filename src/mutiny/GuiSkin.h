#ifndef MUTINY_ENGINE_GUI_SKIN_H
#define MUTINY_ENGINE_GUI_SKIN_H

#include "Object.h"

#include <memory>

namespace mutiny
{

namespace engine
{

class GuiStyle;
class Application;
class Gui;
class GuiSkin : public Object
{
  friend class mutiny::engine::Application;
  friend class mutiny::engine::Gui;

public:
  GuiSkin();

  GuiStyle* getButton();

private:
  static std::shared_ptr<GuiSkin> defaultGuiSkin;

  std::shared_ptr<GuiStyle> button;

};

}

}

#endif

