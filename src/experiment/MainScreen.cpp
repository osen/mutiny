#include "MainScreen.h"

#include <iostream>

using namespace mutiny::engine;

void MainScreen::onAwake()
{
  cameraGo = new GameObject("MainCamera");
  Camera* camera = cameraGo->addComponent<Camera>();
  cameraGo->getTransform()->setPosition(Vector3(0, 1, -10));

  cube1Go = GameObject::createPrimitive(PrimitiveType::CUBE);
  cube1Go->getTransform()->setPosition(Vector3(10, 0, 10));

  cube2Go = GameObject::createPrimitive(PrimitiveType::CUBE);
  cube2Go->getTransform()->setPosition(Vector3(-10, 0, 10));

  cube1Go->getTransform()->setParent(cube2Go->getTransform());
  cube1Go->getTransform()->setParent(NULL);
}

void MainScreen::onGui()
{
  cube2Go->getTransform()->rotate(Vector3(10, 0, 0) * Time::getDeltaTime());
  //cubeGo->getTransform()->translate(Vector3(0, 0, 1) * Time::getDeltaTime());
  //cameraGo->getTransform()->rotate(Vector3(0, 0, 10) * Time::getDeltaTime());
  //cameraGo->getTransform()->translate(Vector3(0, 0, 1) * Time::getDeltaTime());
}

