#include "MainScreen.h"
#include "MainCamera.h"

using namespace mutiny::engine;

void MainScreen::onAwake()
{
  MainCamera::create();
  GameObject::createPrimitive(PrimitiveType::CUBE)->getTransform()->setPosition(Vector3(0, 0, 0));
}

void MainScreen::onGui()
{

}

