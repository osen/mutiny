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

  Graphics::drawTexture(Rect(100, 100, 100, 100), test, Rect(0, 0, 1, 1), 10, 10, 10, 10, Color(1, 1, 1), NULL);
}

