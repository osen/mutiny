#include "SelectModelScreen.h"

using namespace mutiny::engine;

void SelectModelScreen::onAwake()
{
  titleFont = Resources::load<Font>("fonts/default");
}

void SelectModelScreen::onUpdate()
{

}

void SelectModelScreen::onGui()
{
  if(Gui::button(Rect(100, 100, 100, 100), "close") == true)
  {
    Debug::log("I have pressed the close button");
    Application::loadLevel("Main");
  }
}

