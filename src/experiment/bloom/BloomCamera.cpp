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

  lightKeyPass.reset(new RenderTexture(512, 512));
  lightKeyMaterial = Resources::load<Material>("shaders/bloom/light_key");
  lightKeyMaterial->setMatrix("in_View", Matrix4x4::getIdentity());
  lightKeyMaterial->setMatrix("in_Model", Matrix4x4::getIdentity());

  blurPass1.reset(new RenderTexture(512, 512));
  blurPass2.reset(new RenderTexture(512, 512));
  mergePass.reset(new RenderTexture(512, 512));

  getGameObject()->getTransform()->setPosition(Vector3(-10, 0, -18));

  texturedMaterial = Resources::load<Material>("shaders/bloom/blur");
  texturedMaterial->setMatrix("in_View", Matrix4x4::getIdentity());
  texturedMaterial->setMatrix("in_Model", Matrix4x4::getIdentity());
  texturedMaterial->setFloat("in_Direction", 0);

  mergeMaterial = Resources::load<Material>("shaders/bloom/merge");
  mergeMaterial->setMatrix("in_View", Matrix4x4::getIdentity());
  mergeMaterial->setMatrix("in_Model", Matrix4x4::getIdentity());
}

void BloomCamera::onUpdate()
{
  lightKeyMaterial->setMatrix("in_Projection", Matrix4x4::ortho(0, Screen::getWidth(), Screen::getHeight(), 0, -1, 1));
  texturedMaterial->setMatrix("in_Projection", Matrix4x4::ortho(0, Screen::getWidth(), Screen::getHeight(), 0, -1, 1));
  mergeMaterial->setMatrix("in_Projection", Matrix4x4::ortho(0, Screen::getWidth(), Screen::getHeight(), 0, -1, 1));
  getGameObject()->getTransform()->rotateAround(Vector3(-10, 0, -10), Vector3(0, 1, 0), 100.0f * Time::getDeltaTime());
  getGameObject()->getTransform()->lookAt(Vector3(-10, 0, -10));
}

void BloomCamera::onPostRender()
{
  Graphics::setRenderTarget(lightKeyPass.get());
  Graphics::drawTexture(Rect(0, 0, Screen::getWidth(), Screen::getHeight()), originalPass.get(), lightKeyMaterial);
  Graphics::setRenderTarget(NULL);

  Graphics::setRenderTarget(blurPass1.get());
  Graphics::drawTexture(Rect(0, 0, Screen::getWidth(), Screen::getHeight()), lightKeyPass.get(), texturedMaterial);
  Graphics::setRenderTarget(NULL);

  bool swap = false;

  for(int i = 0; i < 6; i++)
  {
    if(swap == false)
    {
      texturedMaterial->setFloat("in_Direction", 0);
      Graphics::setRenderTarget(blurPass2.get());
      Graphics::drawTexture(Rect(0, 0, Screen::getWidth(), Screen::getHeight()), blurPass1.get(), texturedMaterial);
      swap = true;
    }
    else
    {
      texturedMaterial->setFloat("in_Direction", 1);
      Graphics::setRenderTarget(blurPass1.get());
      Graphics::drawTexture(Rect(0, 0, Screen::getWidth(), Screen::getHeight()), blurPass2.get(), texturedMaterial);
      swap = false;
    }

    Graphics::setRenderTarget(NULL);
  }

  Graphics::setRenderTarget(mergePass.get());
  mergeMaterial->setTexture("in_Merge", blurPass1.get());
  Graphics::drawTexture(Rect(0, 0, Screen::getWidth(), Screen::getHeight()), originalPass.get(), mergeMaterial);
  Graphics::setRenderTarget(NULL);

  Gui::drawTexture(Rect(0, 0, Screen::getWidth(), Screen::getHeight()), mergePass.get());
}

