#include "SelectModelScreen.h"
#include "SelectAnimationScreen.h"
#include "../Util.h"

using namespace mutiny::engine;

std::string SelectModelScreen::choice;

void SelectModelScreen::onAwake()
{
  titleFont = Resources::load<Font>("fonts/default");

  Util::scanDir(".", &files);

  for(int i = 0; i < files.size(); i++)
  {
    std::string curr = files.at(i);

    if(curr.length() <= 4 || curr.substr(curr.length() - 4) != ".obj")
    {
      files.erase(files.begin() + i);
      i--;
    }
  }
}

void SelectModelScreen::onUpdate()
{

}

void SelectModelScreen::onGui()
{
  Gui::label(Rect(100, 100, 100, 100), "select a model");

  for(int i = 0; i < files.size(); i++)
  {
    if(Gui::button(Rect(50, 50 + i * 40, 200, 30), Util::cleanPath(files.at(i))) == true)
    {
      choice = files.at(i);
      //Application::loadLevel("Main");
      //Application::loadLevel("SelectAnimation");
      GameObject* go = gcnew<GameObject>("SelectAnimation");
      go->addComponent<SelectAnimationScreen>();
      Object::destroy(this);
    }
  }

  if(Gui::button(Rect(Screen::getWidth() - 110, Screen::getHeight() - 40, 100, 30), "close") == true)
  {
    Application::quit();
  }
}

