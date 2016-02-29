#include "SelectAnimationScreen.h"
#include "SelectModelScreen.h"
#include "../Util.h"

using namespace mutiny::engine;

std::string SelectAnimationScreen::choice;

void SelectAnimationScreen::onAwake()
{
  modelGo = gcnew<GameObject>("Model");
  AnimatedMesh* mesh = Resources::load<AnimatedMesh>(SelectModelScreen::choice.substr(0, SelectModelScreen::choice.length() - 4));
  modelGo->addComponent<AnimatedMeshRenderer>()->setAnimatedMesh(mesh);

  std::string modelDir = Util::pathOnly(SelectModelScreen::choice);

  Debug::log(modelDir);

  Util::scanDir(modelDir, &files);

  for(int i = 0; i < files.size(); i++)
  {
    std::string curr = files.at(i);

    if(curr.length() <= 4 || curr.substr(curr.length() - 4) != ".anm")
    {
      files.erase(files.begin() + i);
      i--;
    }
  }
}

void SelectAnimationScreen::onUpdate()
{

}

void SelectAnimationScreen::onGui()
{
  Gui::label(Rect(100, 100, 100, 100), "select an animation");

  for(int i = 0; i < files.size(); i++)
  {
    if(Gui::button(Rect(50, 50 + i * 40, 200, 30), Util::cleanPath(files.at(i))) == true)
    {
      choice = files.at(i);
      Application::loadLevel("Main");
    }
  }

  if(Gui::button(Rect(Screen::getWidth() - 110, Screen::getHeight() - 40 - 40, 100, 30), "back") == true)
  {
    //Application::loadLevel("SelectModel");
    GameObject* go = gcnew<GameObject>("SelectModel");
    go->addComponent<SelectModelScreen>();
    Object::destroy(this);
  }

  if(Gui::button(Rect(Screen::getWidth() - 110, Screen::getHeight() - 40, 100, 30), "close") == true)
  {
    Application::quit();
  }
}

void SelectAnimationScreen::onDestroy()
{
  Object::destroy(modelGo);
}

