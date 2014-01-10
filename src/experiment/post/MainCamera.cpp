#include "MainCamera.h"

#include <vector>

using namespace mutiny::engine;

MainCamera* MainCamera::create()
{
  GameObject* cameraGo = new GameObject("MainCamera");
  MainCamera* camera = cameraGo->addComponent<MainCamera>();

  return camera;
}

void MainCamera::onAwake()
{
  Debug::log("MainCamera awoken");

  Camera* camera = getGameObject()->addComponent<Camera>();
  originalPass.reset(new RenderTexture(512, 512));
  camera->setTargetTexture(originalPass.get());

  blurPass1.reset(new RenderTexture(64, 64));
  blurPass2.reset(new RenderTexture(128, 128));
  blurPass3.reset(new RenderTexture(256, 256));
  lightKeyPass.reset(new RenderTexture(512, 512));
  mergePass.reset(new RenderTexture(512, 512));

  getGameObject()->getTransform()->setPosition(Vector3(0, 0, -8));

  texturedMaterial = Resources::load<Material>("shaders/simple_2d");
  texturedMaterial->setMatrix("in_Projection", Matrix4x4::ortho(0, Screen::getWidth(), Screen::getHeight(), 0, -1, 1));
  texturedMaterial->setMatrix("in_View", Matrix4x4::getIdentity());
  texturedMaterial->setMatrix("in_Model", Matrix4x4::getIdentity());

  lightKeyMaterial = Resources::load<Material>("shaders/light_key");
  lightKeyMaterial->setMatrix("in_Projection", Matrix4x4::ortho(0, Screen::getWidth(), Screen::getHeight(), 0, -1, 1));
  lightKeyMaterial->setMatrix("in_View", Matrix4x4::getIdentity());
  lightKeyMaterial->setMatrix("in_Model", Matrix4x4::getIdentity());

  mergeMaterial = Resources::load<Material>("shaders/merge");
  mergeMaterial->setMatrix("in_Projection", Matrix4x4::ortho(0, Screen::getWidth(), Screen::getHeight(), 0, -1, 1));
  mergeMaterial->setMatrix("in_View", Matrix4x4::getIdentity());
  mergeMaterial->setMatrix("in_Model", Matrix4x4::getIdentity());
}

void MainCamera::onUpdate()
{
  getGameObject()->getTransform()->rotateAround(Vector3(0, 0, 0), Vector3(0, 1, 0), 100.0f * Time::getDeltaTime());
  getGameObject()->getTransform()->lookAt(Vector3(0, 0, 0));
}

void MainCamera::onGui()
{
  Graphics::setRenderTarget(blurPass1.get());
  Graphics::drawTexture(Rect(-2, -2, Screen::getWidth() + 5, Screen::getHeight() + 5), originalPass.get(), texturedMaterial);
  Graphics::setRenderTarget(NULL);

  Graphics::setRenderTarget(blurPass2.get());
  Graphics::drawTexture(Rect(-2, -2, Screen::getWidth() + 5, Screen::getHeight() + 5), blurPass1.get(), texturedMaterial);
  Graphics::setRenderTarget(NULL);

  Graphics::setRenderTarget(blurPass3.get());
  Graphics::drawTexture(Rect(-2, -2, Screen::getWidth() + 5, Screen::getHeight() + 5), blurPass2.get(), texturedMaterial);
  Graphics::setRenderTarget(NULL);

  Graphics::setRenderTarget(lightKeyPass.get());
  Graphics::drawTexture(Rect(-2, -2, Screen::getWidth() + 5, Screen::getHeight() + 5), blurPass3.get(), lightKeyMaterial);
  Graphics::setRenderTarget(NULL);

  Graphics::setRenderTarget(mergePass.get());
  mergeMaterial->setTexture("in_Merge", lightKeyPass.get());
  Graphics::drawTexture(Rect(0, 0, Screen::getWidth(), Screen::getHeight()), originalPass.get(), mergeMaterial);
  Graphics::setRenderTarget(NULL);

  //Gui::drawTexture(Rect(0, 0, Screen::getWidth(), Screen::getHeight()), originalPass.get());
  //Gui::drawTexture(Rect(0, 0, Screen::getWidth(), Screen::getHeight()), blurPass1.get());
  //Gui::drawTexture(Rect(0, 0, Screen::getWidth(), Screen::getHeight()), blurPass2.get());
  //Gui::drawTexture(Rect(0, 0, Screen::getWidth(), Screen::getHeight()), lightKeyPass.get());
  Gui::drawTexture(Rect(0, 0, Screen::getWidth(), Screen::getHeight()), mergePass.get());
}

