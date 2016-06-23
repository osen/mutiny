#include "MenuScreen.h"
#include "menus/SelectModelScreen.h"

using namespace mutiny::engine;

void MenuScreen::onAwake()
{
  ref<GameObject> cameraGo = GameObject::create("MainCamera");
  cameraGo->addComponent<Camera>();
  cameraGo->getTransform()->translate(Vector3(0, 0, -10));

  ref<GameObject> go = GameObject::create("SelectModel");
  go->addComponent<SelectModelScreen>();
}

void MenuScreen::onUpdate()
{

}

void MenuScreen::onGui()
{

}

