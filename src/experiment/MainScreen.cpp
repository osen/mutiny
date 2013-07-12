#include "MainScreen.h"

#include <iostream>

using namespace mutiny::engine;

void MainScreen::onAwake()
{
  cameraGo = new GameObject("MainCamera");
  Camera* camera = cameraGo->addComponent<Camera>();
  cameraGo->getTransform()->setPosition(Vector3(0, 0, -10));

  cubeGo = GameObject::createPrimitive(PrimitiveType::CUBE);
  //centerGo = GameObject::createPrimitive(PrimitiveType::CUBE);
  cubeGo->getTransform()->setPosition(Vector3(0, 0, 0));

  Matrix4x4 mat = Matrix4x4::getTrs(Vector3(23, 58, 11), Vector3(0, 0, 0), Vector3(1, 1, 1));
  Matrix4x4 mat2 = Matrix4x4::getTrs(Vector3(0, 0, 0), Vector3(86, 49, 11), Vector3(1, 1, 1));

  Vector3 orig(0, 0, 0);
  Matrix4x4 mat3 = Matrix4x4::getIdentity() * mat2 * mat;

  Vector3 result = mat3.multiplyPoint(orig);

  std::cout << result.x << " " << result.y << " " << result.z << std::endl;
}

void MainScreen::onGui()
{
  //cubeGo->getTransform()->rotate(Vector3(10, 0, 0) * Time::getDeltaTime());
  //cubeGo->getTransform()->translate(Vector3(0, 0, 1) * Time::getDeltaTime());
  cameraGo->getTransform()->rotate(Vector3(0, 0, 10) * Time::getDeltaTime());
  //cameraGo->getTransform()->translate(Vector3(0, 0, 1) * Time::getDeltaTime());
}

