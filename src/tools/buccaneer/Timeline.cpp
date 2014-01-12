#include "Timeline.h"

using namespace mutiny::engine;

Timeline* Timeline::create(AnimatedMeshRenderer* amr)
{
  GameObject* go = new GameObject("Timeline");
  Timeline* timeline = go->addComponent<Timeline>();
  timeline->amr = amr;

  return timeline;
}

void Timeline::onAwake()
{
  amr = NULL;
  test = Resources::load<Texture2d>("gui/box_normal");
}

void Timeline::onUpdate()
{

}

void Timeline::onGui()
{
  Gui::box(Rect(10, Screen::getHeight() - 60, Screen::getWidth() - 20, 50), "");

  if(Input::getMouseButton(0) == true)
  {
    //std::cout << (float)amr->getAnimation()->getFrameCount() / (float)Screen::getWidth() * (float)Input::getMousePosition().x << std::endl;
    amr->setFrame((int)((float)amr->getAnimation()->getFrameCount() / (float)Screen::getWidth() * (float)Input::getMousePosition().x));
  }
}

