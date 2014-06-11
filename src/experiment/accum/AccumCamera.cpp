#include "AccumCamera.h"

#include <vector>

using namespace mutiny::engine;

AccumCamera* AccumCamera::create()
{
  GameObject* cameraGo = new GameObject("AccumCamera");
  AccumCamera* camera = cameraGo->addComponent<AccumCamera>();

  return camera;
}

void AccumCamera::onAwake()
{
  Debug::log("AccumCamera awoken");

  Camera* camera = getGameObject()->addComponent<Camera>();
  //camera->setBackgroundColor(Color(0, 0, 0, 1));
  camera->setBackgroundColor(Color(0.0f, 0.0f, 0.10f, 1));

  regenRenderTextures();

  lightKeyMaterial = Resources::load<Material>("shaders/accum/light_key");
  texturedMaterial = Resources::load<Material>("shaders/accum/blur");
  mergeMaterial = Resources::load<Material>("shaders/accum/merge");
  accumMaterial = Resources::load<Material>("shaders/accum/accum");
  deaccumMaterial = Resources::load<Material>("shaders/accum/deaccum");

  lightKeyMaterial->setMatrix("in_Projection", Matrix4x4::ortho(0, 1, 1, 0, -1, 1));
  texturedMaterial->setMatrix("in_Projection", Matrix4x4::ortho(0, 1, 1, 0, -1, 1));
  texturedMaterial->setFloat("in_Direction", 0);
  mergeMaterial->setMatrix("in_Projection", Matrix4x4::ortho(0, 1, 1, 0, -1, 1));
  accumMaterial->setMatrix("in_Projection", Matrix4x4::ortho(0, 1, 1, 0, -1, 1));
  deaccumMaterial->setMatrix("in_Projection", Matrix4x4::ortho(0, 1, 1, 0, -1, 1));

  getGameObject()->getTransform()->setPosition(Vector3(0, 3, 13));
  getGameObject()->getTransform()->lookAt(Vector3(0, 0, 0));
}

void AccumCamera::regenRenderTextures()
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
  blurPass1.reset(new RenderTexture(idealWidth/2.0f, idealHeight/2.0f));
  blurPass2.reset(new RenderTexture(idealWidth/2.0f, idealHeight/2.0f));
  mergePass.reset(new RenderTexture(idealWidth, idealHeight));
  accumPass.reset(new RenderTexture(idealWidth, idealHeight));
  deaccumPass.reset(new RenderTexture(idealWidth, idealHeight));

  accumA = accumPass.get();
  accumB = deaccumPass.get();

  getGameObject()->getComponent<Camera>()->setTargetTexture(originalPass.get());
}

void AccumCamera::onUpdate()
{
  //getGameObject()->getTransform()->rotateAround(Vector3(-10, 0, -10), Vector3(0, 1, 0), 100.0f * Time::getDeltaTime());
  regenRenderTextures();
}

void AccumCamera::onPostRender()
{
  Rect rect(0, 0, 1, 1);

  Graphics::setRenderTarget(lightKeyPass.get());
  Graphics::drawTexture(rect, originalPass.get(), lightKeyMaterial);
  Graphics::setRenderTarget(NULL);

  Graphics::setRenderTarget(accumA);
  Graphics::drawTexture(rect, lightKeyPass.get(), accumMaterial);
  Graphics::setRenderTarget(NULL);

  deaccumMaterial->setFloat("in_TimeDelta", Time::getDeltaTime());
  Graphics::setRenderTarget(accumB);
  Graphics::drawTexture(rect, accumA, deaccumMaterial);
  Graphics::setRenderTarget(NULL);

  RenderTexture* tmp = accumA;
  accumA = accumB;
  accumB = tmp;

  Graphics::setRenderTarget(blurPass1.get());
  Graphics::drawTexture(rect, accumB, texturedMaterial);
  Graphics::setRenderTarget(NULL);

  bool swap = false;

  int idealWidth = Mathf::nextPowerOfTwo(Screen::getWidth());
  int idealHeight = Mathf::nextPowerOfTwo(Screen::getHeight());

  for(int i = 0; i < 6; i++)
  {
    if(swap == false)
    {
      texturedMaterial->setVector("in_Scale", Vector2(1.0f / ((float)idealWidth * 0.3f), 0));
      Graphics::setRenderTarget(blurPass2.get());
      Graphics::drawTexture(rect, blurPass1.get(), texturedMaterial);
      swap = true;
    }
    else
    {
      texturedMaterial->setVector("in_Scale", Vector2(0, 1.0f / ((float)idealHeight * 0.3f)));
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
  //Gui::drawTexture(Rect(0, 0, Screen::getWidth(), Screen::getHeight()), accumA);
}

