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

  ref<GuiStyle> getButton();
  ref<GuiStyle> getBox();

private:
  shared<GuiStyle> button;
  shared<GuiStyle> box;

};

}

}

#endif

