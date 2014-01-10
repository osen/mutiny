#include "BloomCamera.h"

#include <vector>

using namespace mutiny::engine;

BloomCamera* BloomCamera::create()
{
  GameObject* cameraGo = new GameObject("BloomCamera");
  BloomCamera* camera = cameraGo->addComponent<BloomCamera>();

  return camera;
}

void BloomCamera::onAwake()
{
  Debug::log("BloomCamera awoken");

  Camera* camera = getGameObject()->addComponent<Camera>();
  camera->setBackgroundColor(Color(0, 0, 0, 1));
  originalPass.reset(new RenderTexture(512, 512));
  camera->setTargetTexture(originalPass.get());

  blurPass1.reset(new RenderTexture(64, 64));
  blurPass2.reset(new RenderTexture(128, 128));
  blurPass3.reset(new RenderTexture(256, 256));
  mergePass.reset(new RenderTexture(512, 512));

  getGameObject()->getTransform()->setPosition(Vector3(0, 0, -8));

  texturedMaterial = Resources::load<Material>("shaders/bloom/simple_2d");
  texturedMaterial->setMatrix("in_Projection", Matrix4x4::ortho(0, Screen::getWidth(), Screen::getHeight(), 0, -1, 1));
  texturedMaterial->setMatrix("in_View", Matrix4x4::getIdentity());
  texturedMaterial->setMatrix("in_Model", Matrix4x4::getIdentity());

  mergeMaterial = Resources::load<Material>("shaders/bloom/merge");
  mergeMaterial->setMatrix("in_Projection", Matrix4x4::ortho(0, Screen::getWidth(), Screen::getHeight(), 0, -1, 1));
  mergeMaterial->setMatrix("in_View", Matrix4x4::getIdentity());
  mergeMaterial->setMatrix("in_Model", Matrix4x4::getIdentity());
}

void BloomCamera::onUpdate()
{
  getGameObject()->getTransform()->rotateAround(Vector3(0, 0, 0), Vector3(0, 1, 0), 100.0f * Time::getDeltaTime());
  getGameObject()->getTransform()->lookAt(Vector3(0, 0, 0));
}

void BloomCamera::onGui()
{
  Graphics::setRenderTarget(blurPass1.get());
  //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  Graphics::drawTexture(Rect(-2, -2, Screen::getWidth() + 5, Screen::getHeight() + 5), originalPass.get(), texturedMaterial);
  Graphics::setRenderTarget(NULL);

  Graphics::setRenderTarget(blurPass2.get());
  //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  Graphics::drawTexture(Rect(-2, -2, Screen::getWidth() + 5, Screen::getHeight() + 5), blurPass1.get(), texturedMaterial);
  Graphics::setRenderTarget(NULL);

  Graphics::setRenderTarget(blurPass3.get());
  //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  Graphics::drawTexture(Rect(-2, -2, Screen::getWidth() + 5, Screen::getHeight() + 5), blurPass2.get(), texturedMaterial);
  Graphics::setRenderTarget(NULL);

  Graphics::setRenderTarget(mergePass.get());
  //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  mergeMaterial->setTexture("in_Merge", blurPass3.get());
  Graphics::drawTexture(Rect(0, 0, Screen::getWidth(), Screen::getHeight()), originalPass.get(), mergeMaterial);
  Graphics::setRenderTarget(NULL);

  Gui::drawTexture(Rect(0, 0, Screen::getWidth(), Screen::getHeight()), mergePass.get());
}

