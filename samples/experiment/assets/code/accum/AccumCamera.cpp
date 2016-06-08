#include "AccumCamera.h"

#include <vector>

using namespace mutiny::engine;

ref<AccumCamera> AccumCamera::create()
{
  ref<GameObject> cameraGo = GameObject::create("AccumCamera");
  ref<AccumCamera> camera = cameraGo->addComponent<AccumCamera>();

  return camera;
}

void AccumCamera::onAwake()
{
  Debug::log("AccumCamera awoken");

  ref<Camera> camera = getGameObject()->addComponent<Camera>();
  //camera->setBackgroundColor(Color(0, 0, 0, 1));
  camera->setBackgroundColor(Color(0.5f, 0.5f, 0.6f, 1));

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

  originalPass = RenderTexture::create(idealWidth, idealHeight);
  lightKeyPass = RenderTexture::create(idealWidth, idealHeight);
  blurPass1 = RenderTexture::create(idealWidth/2.0f, idealHeight/2.0f);
  blurPass2 = RenderTexture::create(idealWidth/2.0f, idealHeight/2.0f);
  mergePass = RenderTexture::create(idealWidth, idealHeight);
  accumPass = RenderTexture::create(idealWidth, idealHeight);
  deaccumPass = RenderTexture::create(idealWidth, idealHeight);

  accumA = accumPass;
  accumB = deaccumPass;

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
  Graphics::drawTexture(rect, originalPass.get(), lightKeyMaterial.get());
  Graphics::setRenderTarget(NULL);

  Graphics::setRenderTarget(accumA.get());
  Graphics::drawTexture(rect, lightKeyPass.get(), accumMaterial.get());
  Graphics::setRenderTarget(NULL);

  deaccumMaterial->setFloat("in_TimeDelta", Time::getDeltaTime());
  Graphics::setRenderTarget(accumB.get());
  Graphics::drawTexture(rect, accumA.get(), deaccumMaterial.get());
  Graphics::setRenderTarget(NULL);

  shared<RenderTexture> tmp = accumA;
  accumA = accumB;
  accumB = tmp;

  Graphics::setRenderTarget(blurPass1.get());
  Graphics::drawTexture(rect, accumB.get(), texturedMaterial.get());
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
      Graphics::drawTexture(rect, blurPass1.get(), texturedMaterial.get());
      swap = true;
    }
    else
    {
      texturedMaterial->setVector("in_Scale", Vector2(0, 1.0f / ((float)idealHeight * 0.3f)));
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
  //Gui::drawTexture(Rect(0, 0, Screen::getWidth(), Screen::getHeight()), accumA);
}

