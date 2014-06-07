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

  originalPass.reset(new RenderTexture(512, 512));
  lightKeyPass.reset(new RenderTexture(512, 512));
  blurPass1.reset(new RenderTexture(512, 512));
  blurPass2.reset(new RenderTexture(512, 512));
  mergePass.reset(new RenderTexture(512, 512));

  lightKeyMaterial = Resources::load<Material>("shaders/bloom/light_key");
  texturedMaterial = Resources::load<Material>("shaders/bloom/blur");
  mergeMaterial = Resources::load<Material>("shaders/bloom/merge");

  lightKeyMaterial->setMatrix("in_Projection", Matrix4x4::ortho(0, 1, 1, 0, -1, 1));
  texturedMaterial->setMatrix("in_Projection", Matrix4x4::ortho(0, 1, 1, 0, -1, 1));
  texturedMaterial->setFloat("in_Direction", 0);
  mergeMaterial->setMatrix("in_Projection", Matrix4x4::ortho(0, 1, 1, 0, -1, 1));

  Camera* camera = getGameObject()->addComponent<Camera>();
  camera->setBackgroundColor(Color(0, 0, 0, 1));
  camera->setTargetTexture(originalPass.get());

  getGameObject()->getTransform()->setPosition(Vector3(-10, 0, -18));
}

void BloomCamera::onUpdate()
{
  getGameObject()->getTransform()->rotateAround(Vector3(-10, 0, -10), Vector3(0, 1, 0), 100.0f * Time::getDeltaTime());
  getGameObject()->getTransform()->lookAt(Vector3(-10, 0, -10));
}

void BloomCamera::onPostRender()
{
  Rect rect(0, 0, 1, 1);

  Graphics::setRenderTarget(lightKeyPass.get());
  Graphics::drawTexture(rect, originalPass.get(), lightKeyMaterial);
  Graphics::setRenderTarget(NULL);

  Graphics::setRenderTarget(blurPass1.get());
  Graphics::drawTexture(rect, lightKeyPass.get(), texturedMaterial);
  Graphics::setRenderTarget(NULL);

  bool swap = false;

  for(int i = 0; i < 6; i++)
  {
    if(swap == false)
    {
      texturedMaterial->setFloat("in_Direction", 0);
      Graphics::setRenderTarget(blurPass2.get());
      Graphics::drawTexture(rect, blurPass1.get(), texturedMaterial);
      swap = true;
    }
    else
    {
      texturedMaterial->setFloat("in_Direction", 1);
      Graphics::setRenderTarget(blurPass1.get());
      Graphics::drawTexture(rect, blurPass2.get(), texturedMaterial);
      swap = false;
    }

    Graphics::setRenderTarget(NULL);
  }

  Graphics::setRenderTarget(mergePass.get());
  mergeMaterial->setTexture("in_Merge", blurPass1.get());
  Graphics::drawTexture(rect, originalPass.get(), mergeMaterial);
  Graphics::setRenderTarget(NULL);

  Gui::drawTexture(Rect(0, 0, Screen::getWidth(), Screen::getHeight()), mergePass.get());
}

