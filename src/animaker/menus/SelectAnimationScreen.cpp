#include "SelectAnimationScreen.h"
#include "SelectModelScreen.h"

using namespace mutiny::engine;

std::string SelectAnimationScreen::choice;

void SelectAnimationScreen::onAwake()
{
  modelGo = new GameObject("Model");
  modelGo->addComponent<MeshRenderer>();
  MeshFilter* mf = modelGo->addComponent<MeshFilter>();
  mf->setMesh(Resources::load<Mesh>(SelectModelScreen::choice.substr(0, SelectModelScreen::choice.length() - 4)));
}

void SelectAnimationScreen::onUpdate()
{

}

void SelectAnimationScreen::onGui()
{
  Gui::label(Rect(100, 100, 100, 100), "select an animation");

  if(Gui::button(Rect(Screen::getWidth() - 110, Screen::getHeight() - 40 - 40, 100, 30), "back") == true)
  {
    //Application::loadLevel("SelectModel");
    GameObject* go = new GameObject("SelectModel");
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

