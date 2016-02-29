#include "MenuScreen.h"
#include "menus/SelectModelScreen.h"

using namespace mutiny::engine;

void MenuScreen::onAwake()
{
  GameObject* cameraGo = gcnew<GameObject>("MainCamera");
  cameraGo->addComponent<Camera>();
  cameraGo->getTransform()->translate(Vector3(0, 0, -10));

  GameObject* go = gcnew<GameObject>("SelectModel");
  go->addComponent<SelectModelScreen>();
}

void MenuScreen::onUpdate()
{

}

void MenuScreen::onGui()
{

}

