#include "Timeline.h"
#include "MainScreen.h"

using namespace mutiny::engine;

Timeline* Timeline::create(MainScreen* mainScreen)
{
  GameObject* go = new GameObject("Timeline");
  Timeline* timeline = go->addComponent<Timeline>();
  timeline->mainScreen = mainScreen;
  timeline->amr = mainScreen->amr;

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
  if(amr->isPlaying() == true)
  {
    return;
  }

  int spacer = 50;
  Gui::box(Rect(spacer, Screen::getHeight() - 60, Screen::getWidth() - (spacer * 2), 50), "");
  float pointWidth = (Screen::getWidth() - spacer - spacer) / (amr->getAnimation()->getFrameCount() - 1);
  int relX = Input::getMousePosition().x - spacer + (pointWidth / 2);

  for(int i = 1; i < amr->getAnimation()->getFrameCount() - 1; i++)
  {
    Gui::box(Rect(spacer + (i * pointWidth), Screen::getHeight() - 60, 2, 50), "");
  }

  if(Input::getMouseButton(0) == true &&
     Input::getMousePosition().y >= Screen::getHeight() - 60 &&
     Input::getMousePosition().x > spacer)
  {
    amr->setFrame((int)((float)(amr->getAnimation()->getFrameCount() - 1.0f) / (float)(Screen::getWidth() - spacer - spacer) * (float)relX));
    //std::cout << amr->getFrame() << std::endl;
  }

  if(Gui::button(Rect(10, Screen::getHeight() - 60, 40, 50), "Add") == true)
  {
    amr->getAnimation()->frames.insert(amr->getAnimation()->frames.begin() + amr->getFrame(), amr->getAnimation()->frames.at(amr->getFrame()));
    amr->setFrame(amr->getFrame() + 1);
    mainScreen->undoBuffer.push_back(mainScreen->animation->frames);
  }
}

