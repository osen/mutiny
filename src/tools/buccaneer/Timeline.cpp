#include "Timeline.h"

using namespace mutiny::engine;

Timeline* Timeline::create()
{
  GameObject* go = new GameObject("Timeline");
  return go->addComponent<Timeline>();
}

void Timeline::onAwake()
{
  frame = 0;
  test = Resources::load<Texture2d>("gui/box_normal");
}

int Timeline::getFrame()
{
  return frame;
}

void Timeline::onUpdate()
{

}

void Timeline::onGui()
{
  Gui::box(Rect(10, Screen::getHeight() - 60, Screen::getWidth() - 20, 50), "");
}

