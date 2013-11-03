#include "Timeline.h"

using namespace mutiny::engine;

Timeline* Timeline::create()
{
  GameObject* go = new GameObject("Timeline");
  return go->addComponent<Timeline>();
}

void Timeline::onAwake()
{
  test = Resources::load<Texture2d>("gui/box_normal");
}

void Timeline::onUpdate()
{

}

void Timeline::onGui()
{
  Gui::box(Rect(10, Screen::getHeight() - 60, Screen::getWidth() - 20, 50), "");
}

