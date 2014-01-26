#include "GameCamera.h"

#include <iostream>

using namespace mutiny::engine;

GameObject* GameCamera::create(GameObject* playerGo)
{
  GameObject* mainGo = new GameObject("GameCamera");
  GameCamera* gameCamera = mainGo->addComponent<GameCamera>();
  gameCamera->playerGo = playerGo;

  return mainGo;
}

void GameCamera::toggleEventMode()
{
  if(eventMode == true)
    eventMode = false;
  else
    eventMode = true;
}

void GameCamera::onAwake()
{
  eventMode = false;
  camera = getGameObject()->addComponent<Camera>();
  camera->setBackgroundColor(Color(0, 0, 0, 1));
  originalPass.reset(new RenderTexture(512, 512));
  camera->setTargetTexture(originalPass.get());

  blurPass1.reset(new RenderTexture(64, 64));
  blurPass2.reset(new RenderTexture(256, 256));
  blurPass3.reset(new RenderTexture(64, 64));
  mergePass.reset(new RenderTexture(512, 512));

  getGameObject()->getTransform()->setPosition(Vector3(0, 0, -8));

  texturedMaterial = Resources::load<Material>("shaders/bloom/simple_2d");
  texturedMaterial->setMatrix("in_Projection", Matrix4x4::ortho(0, 
    Screen::getWidth(), Screen::getHeight(), 0, -1, 1));
  texturedMaterial->setMatrix("in_View", Matrix4x4::getIdentity());
  texturedMaterial->setMatrix("in_Model", Matrix4x4::getIdentity());

  mergeMaterial = Resources::load<Material>("shaders/bloom/merge");
  mergeMaterial->setMatrix("in_Projection", Matrix4x4::ortho(0, 
    Screen::getWidth(), Screen::getHeight(), 0, -1, 1));
  mergeMaterial->setMatrix("in_View", Matrix4x4::getIdentity());
  mergeMaterial->setMatrix("in_Model", Matrix4x4::getIdentity());
}

void GameCamera::onUpdate()
{
  Vector3 final;

  if(eventMode == true)
  {
    rotationBuffer.push_back(Vector3(20, 180, 0));
    positionBuffer.push_back(playerGo->getTransform()->getPosition() + Vector3(0, 5, 10));
  }
  else
  {
    rotationBuffer.push_back(Vector3(20, 0, 0));
    positionBuffer.push_back(playerGo->getTransform()->getPosition() + Vector3(0, 5, -10));
  }

  while(positionBuffer.size() > 10)
    positionBuffer.erase(positionBuffer.begin() + 0);

  while(rotationBuffer.size() > 10)
    rotationBuffer.erase(rotationBuffer.begin() + 0);

  for(int i = 0; i < positionBuffer.size(); i++)
    final = final + positionBuffer.at(i);

  final = final / positionBuffer.size();

  getGameObject()->getTransform()->setPosition(final);
  final = Vector3();

  for(int i = 0; i < rotationBuffer.size(); i++)
    final = final + rotationBuffer.at(i);

  final = final / rotationBuffer.size();

  getGameObject()->getTransform()->setRotation(final);
}

void GameCamera::onStart()
{
  getGameObject()->getTransform()->setPosition(Vector3(0, 15, -35));
  getGameObject()->getTransform()->setRotation(Vector3(20, 0, 0));
}

void GameCamera::onPostRender()
{
  Graphics::setRenderTarget(blurPass1.get());
  Graphics::drawTexture(Rect(-2, -2, Screen::getWidth() + 5, Screen::getHeight() + 5), 
    originalPass.get(), texturedMaterial);
  Graphics::setRenderTarget(NULL);

  Graphics::setRenderTarget(blurPass2.get());
  Graphics::drawTexture(Rect(-2, -2, Screen::getWidth() + 5, Screen::getHeight() + 5), 
    blurPass1.get(), texturedMaterial);
  Graphics::setRenderTarget(NULL);

  Graphics::setRenderTarget(blurPass3.get());
  Graphics::drawTexture(Rect(-2, -2, Screen::getWidth() + 5, Screen::getHeight() + 5), 
    blurPass2.get(), texturedMaterial);
  Graphics::setRenderTarget(NULL);

  Graphics::setRenderTarget(mergePass.get());
  mergeMaterial->setTexture("in_Merge", blurPass3.get());
  Graphics::drawTexture(Rect(0, 0, Screen::getWidth(), Screen::getHeight()), 
    originalPass.get(), mergeMaterial);
  Graphics::setRenderTarget(NULL);

  Gui::drawTexture(Rect(0, 0, Screen::getWidth(), Screen::getHeight()), mergePass.get());
}

