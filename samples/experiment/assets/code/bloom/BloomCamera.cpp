#include "BloomCamera.h"

#include <vector>

using namespace mutiny::engine;

BloomCamera* BloomCamera::create()
{
  GameObject* cameraGo = GameObject::create("BloomCamera");
  BloomCamera* camera = cameraGo->addComponent<BloomCamera>();

  return camera;
}

void BloomCamera::onAwake()
{
  Debug::log("BloomCamera awoken");

  Camera* camera = getGameObject()->addComponent<Camera>();
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

  originalPass.reset(new RenderTexture(idealWidth, idealHeight));
  lightKeyPass.reset(new RenderTexture(idealWidth, idealHeight));
  blurPass1.reset(new RenderTexture(idealWidth, idealHeight));
  blurPass2.reset(new RenderTexture(idealWidth, idealHeight));
  mergePass.reset(new RenderTexture(idealWidth, idealHeight));

  getGameObject()->getComponent<Camera>()->setTargetTexture(originalPass);
}

void BloomCamera::onUpdate()
{
  //getGameObject()->getTransform()->rotateAround(Vector3(-10, 0, -10), Vector3(0, 1, 0), 100.0f * Time::getDeltaTime());
  regenRenderTextures();
}

void BloomCamera::onPostRender()
{
  Rect rect(0, 0, 1, 1);

  Graphics::setRenderTarget(lightKeyPass);
  Graphics::drawTexture(rect, originalPass.cast<Texture>(), lightKeyMaterial);
  Graphics::setRenderTarget(arc<RenderTexture>());

  Graphics::setRenderTarget(blurPass1);
  Graphics::drawTexture(rect, lightKeyPass.cast<Texture>(), texturedMaterial);
  Graphics::setRenderTarget(arc<RenderTexture>());

  bool swap = false;
  int idealWidth = Mathf::nextPowerOfTwo(Screen::getWidth());
  int idealHeight = Mathf::nextPowerOfTwo(Screen::getHeight());

  for(int i = 0; i < 6; i++)
  {
    if(swap == false)
    {
      texturedMaterial->setVector("in_Scale", Vector2(1.0f / ((float)idealWidth * 0.4f), 0));
      Graphics::setRenderTarget(blurPass2);
      Graphics::drawTexture(rect, blurPass1.cast<Texture>(), texturedMaterial);
      swap = true;
    }
    else
    {
      texturedMaterial->setVector("in_Scale", Vector2(0, 1.0f / ((float)idealHeight * 0.4f)));
      Graphics::setRenderTarget(blurPass1);
      Graphics::drawTexture(rect, blurPass2.cast<Texture>(), texturedMaterial);
      swap = false;
    }

    Graphics::setRenderTarget(arc<RenderTexture>());
  }

  Graphics::setRenderTarget(mergePass);
  mergeMaterial->setTexture("in_Merge", blurPass1.cast<Texture>());
  Graphics::drawTexture(rect, originalPass.cast<Texture>(), mergeMaterial);
  Graphics::setRenderTarget(arc<RenderTexture>());

  Gui::drawTexture(Rect(0, 0, Screen::getWidth(), Screen::getHeight()), mergePass.cast<Texture>());
}

