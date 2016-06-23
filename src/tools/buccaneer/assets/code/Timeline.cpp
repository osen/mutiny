#include "Timeline.h"
#include "MainScreen.h"

using namespace mutiny::engine;

ref<Timeline> Timeline::create(ref<MainScreen> mainScreen)
{
  ref<GameObject> go = GameObject::create("Timeline");
  ref<Timeline> timeline = go->addComponent<Timeline>();
  timeline->mainScreen = mainScreen;
  timeline->amr = mainScreen->amr;

  return timeline;
}

void Timeline::onAwake()
{
  amr = NULL;
  test = Resources::load<Texture2d>("gui/box_normal");
  whitePixel = Resources::load<Texture2d>("images/white_pixel");
  cursor = Resources::load<Texture2d>("images/cursor");
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

  int spacer = 60;
  //Gui::box(Rect(spacer, Screen::getHeight() - 60, Screen::getWidth() - (spacer * 2), 50), "");
  Gui::drawTexture(Rect(spacer, Screen::getHeight() - 10 - 10 - 1, Screen::getWidth() - (spacer * 2), 2), whitePixel.get());

  float pointWidth = Screen::getWidth() - spacer - spacer;

  if(amr->getAnimation()->getFrameCount() > 1)
  {
    pointWidth = pointWidth / (amr->getAnimation()->getFrameCount() - 1);
  }

  int relX = Input::getMousePosition().x - spacer + (pointWidth / 2);

  for(int i = 0; i < amr->getAnimation()->getFrameCount(); i++)
  {
    Gui::drawTexture(Rect(spacer + (i * pointWidth) - 1, Screen::getHeight() - 10 - 10 - 8, 2, 9), whitePixel.get());

    if(i == amr->getFrame())
    {
      Gui::drawTexture(Rect(spacer + (i * pointWidth) - (cursor->getWidth() / 2), Screen::getHeight() - 10 - 10 - cursor->getHeight(), cursor->getWidth(), cursor->getHeight()), cursor.get());
    }
  }

  if(Input::getMouseButton(0) == true &&
     Input::getMousePosition().y >= Screen::getHeight() - 60 &&
     Input::getMousePosition().x > spacer &&
     Input::getMousePosition().x < Screen::getWidth() - spacer)
  {
    amr->setFrame((int)((float)(amr->getAnimation()->getFrameCount() - 1.0f) / (float)(Screen::getWidth() - spacer - spacer) * (float)relX));
    //std::cout << amr->getFrame() << std::endl;
  }

  if(Gui::button(Rect(10, Screen::getHeight() - 60, 40, 50), "Add") == true)
  {
    amr->getAnimation()->frames.insert(amr->getAnimation()->frames.begin() + amr->getFrame(), AnimationFrame::copy(amr->getAnimation()->frames.at(amr->getFrame())));
    amr->setFrame(amr->getFrame() + 1);
    mainScreen->undoBuffer.push_back(mainScreen->animation->frames);
  }

  if(Gui::button(Rect(Screen::getWidth() - 10 - 40, Screen::getHeight() - 60, 40, 50), "Del") == true)
  {
    amr->getAnimation()->frames.erase(amr->getAnimation()->frames.begin() + amr->getFrame());

    if(amr->getAnimation()->frames.size() < 1)
    {
      amr->getAnimation()->frames.push_back(shared<AnimationFrame>());
      amr->setFrame(0);
    }
    else
    {
      amr->setFrame(amr->getFrame() - 1);
    }

    mainScreen->undoBuffer.push_back(mainScreen->animation->frames);
  }
}

