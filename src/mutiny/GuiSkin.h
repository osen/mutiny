#ifndef MUTINY_ENGINE_GUI_SKIN_H
#define MUTINY_ENGINE_GUI_SKIN_H

#include "Object.h"
#include "arc.h"

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

  arc<GuiStyle> getButton();
  arc<GuiStyle> getBox();

private:
  static GuiSkin* _default;

  arc<GuiStyle> button;
  arc<GuiStyle> box;

};

}

}

#endif

