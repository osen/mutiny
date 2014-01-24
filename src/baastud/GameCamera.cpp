#include "GameCamera.h"

#include <iostream>

using namespace mutiny::engine;

GameObject* GameCamera::create()
{
  GameObject* mainGo = new GameObject("GameCamera");
  mainGo->addComponent<GameCamera>();

  return mainGo;
}

void GameCamera::onAwake()
{
  camera = getGameObject()->addComponent<Camera>();
}

