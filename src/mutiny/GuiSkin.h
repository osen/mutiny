#ifndef MUTINY_ENGINE_GUI_SKIN_H
#define MUTINY_ENGINE_GUI_SKIN_H

#include "GuiStyle.h"

#include <memory>

namespace mutiny
{

namespace engine
{

class Application;
class GuiSkin
{
  friend class mutiny::engine::Application;

public:

private:
  static std::shared_ptr<GuiSkin> defaultGuiSkin;

  std::shared_ptr<GuiStyle> button;

};

}

}

#endif

