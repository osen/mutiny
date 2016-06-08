#ifndef MUTINY_ENGINE_GUISTYLESTATE_H
#define MUTINY_ENGINE_GUISTYLESTATE_H

#include "ref.h"

#include <memory>

namespace mutiny
{

namespace engine
{

class Texture2d;
class GuiStyleState : public enable_ref
{
public:
  GuiStyleState();

  void setBackground(ref<Texture2d> background);
  ref<Texture2d> getBackground();

private:
  shared<Texture2d> defaultBackground;
  ref<Texture2d> background;

};

}

}

#endif

