#include "BloomCamera.h"

#include <vector>

using namespace mutiny::engine;

ref<BloomCamera> BloomCamera::create()
{
  ref<GameObject> cameraGo = GameObject::create("BloomCamera");
  ref<BloomCamera> camera = cameraGo->addComponent<BloomCamera>();

  return camera;
}

void BloomCamera::onAwake()
{
  Debug::log("BloomCamera awoken");

  ref<Camera> camera = getGameObject()->addComponent<Camera>();
  camera->setBackgroundColor(Color(0, 0, 0, 1));

  regenRenderTextures();

  lightKeyMaterial = Resources::load<Material>("shaders/bloom/light_key");
  texturedMaterial = Resources::load<Material>("shaders/bloom/blur");
  mergeMaterial = Resources::load<Material>("shaders/bloom/merge");

  lightKeyMaterial->setMatrix("in_Projection", Matrix4x4::ortho(0, 1, 1, 0, -1, 1));
  texturedMaterial->setMatrix("in_Projection", Matrix4x4::ortho(0, 1, 1, 0, -1, 1));
  texturedMaterial->setFloat("in_Direction", 0);
  mergeMaterial->setMatrix("in_Projection", Matrix4x4::ortho(0, 1, 1, 0, -1, 1));

  getGameObject()->getTransform()->setPosition(Vector3(-5, 0, -5));
  getGameObject()->getTransform()->lookAt(Vector3(-10, 0, -10));
}

void BloomCamera::regenRenderTextures()
{
  int idealWidth = Mathf::nextPowerOfTwo(Screen::getWidth());
  int idealHeight = Mathf::nextPowerOfTwo(Screen::getHeight());

  if(originalPass.get() != NULL)
  {
    if(originalPass->getWidth() == idealWidth &&
       originalPass->getHeight() == idealHeight)
    {
      return;
    }
  }

  Debug::logWarning("Resizing render textures");

  originalPass = RenderTexture::create(idealWidth, idealHeight);
  lightKeyPass = RenderTexture::create(idealWidth, idealHeight);
  blurPass1 = RenderTexture::create(idealWidth, idealHeight);
  blurPass2 = RenderTexture::create(idealWidth, idealHeight);
  mergePass = RenderTexture::create(idealWidth, idealHeight);

  getGameObject()->getComponent<Camera>()->setTargetTexture(originalPass.get());
}

void BloomCamera::onUpdate()
{
  //getGameObject()->getTransform()->rotateAround(Vector3(-10, 0, -10), Vector3(0, 1, 0), 100.0f * Time::getDeltaTime());
  regenRenderTextures();
}

void BloomCamera::onPostRender()
{
  Rect rect(0, 0, 1, 1);

  Graphics::setRenderTarget(lightKeyPass.get());
  Graphics::drawTexture(rect, originalPass.get(), lightKeyMaterial.get());
  Graphics::setRenderTarget(NULL);

  Graphics::setRenderTarget(blurPass1.get());
  Graphics::drawTexture(rect, lightKeyPass.get(), texturedMaterial.get());
  Graphics::setRenderTarget(NULL);

  bool swap = false;
  int idealWidth = Mathf::nextPowerOfTwo(Screen::getWidth());
  int idealHeight = Mathf::nextPowerOfTwo(Screen::getHeight());

  for(int i = 0; i < 6; i++)
  {
    if(swap == false)
    {
      texturedMaterial->setVector("in_Scale", Vector2(1.0f / ((float)idealWidth * 0.4f), 0));
      Graphics::setRenderTarget(blurPass2.get());
      Graphics::drawTexture(rect, blurPass1.get(), texturedMaterial.get());
      swap = true;
    }
    else
    {
      texturedMaterial->setVector("in_Scale", Vector2(0, 1.0f / ((float)idealHeight * 0.4f)));
      Graphics::setRenderTarget(blurPass1.get());
      Graphics::drawTexture(rect, blurPass2.get(), texturedMaterial.get());
      swap = false;
    }

    Graphics::setRenderTarget(NULL);
  }

  Graphics::setRenderTarget(mergePass.get());
  mergeMaterial->setTexture("in_Merge", blurPass1.get());
  Graphics::drawTexture(rect, originalPass.get(), mergeMaterial.get());
  Graphics::setRenderTarget(NULL);

  Gui::drawTexture(Rect(0, 0, Screen::getWidth(), Screen::getHeight()), mergePass.get());
}

