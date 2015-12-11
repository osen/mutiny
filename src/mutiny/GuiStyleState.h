#ifndef MUTINY_ENGINE_GUISTYLESTATE_H
#define MUTINY_ENGINE_GUISTYLESTATE_H

#include "arc.h"

#include <memory>

namespace mutiny
{

namespace engine
{

class Texture2d;
class GuiStyleState
{
public:
  GuiStyleState();

  void setBackground(Texture2d* background);
  Texture2d* getBackground();

private:
  arc<Texture2d> defaultBackground;
  Texture2d* background;

};

}

}

#endif

