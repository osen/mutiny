#include "LayerScreen.h"
#include "LayerCamera.h"

using namespace mutiny::engine;

GameObject* LayerScreen::create()
{
  GameObject* mainGo = new GameObject("LayerScreen");
  mainGo->addComponent<LayerScreen>();

  return mainGo;
}

void LayerScreen::onAwake()
{
  cameraGo = LayerCamera::create();

  playerGo = new GameObject("Player");
  //playerGo->setLayer(1 << 1);
  playerGo->getTransform()->setPosition(Vector3(0, 0, 0));

  MeshRenderer* playerMr = playerGo->addComponent<MeshRenderer>();
  playerMr->setMaterial(Resources::load<Material>("shaders/textured"));
  playerMr->getMaterial()->setMainTexture(Resources::load<Texture2d>("models/curuthers/Whiskers_diffuse"));

  Mesh* mesh = Resources::load<Mesh>("models/curuthers/curuthers");
  MeshFilter* playerMf = playerGo->addComponent<MeshFilter>();
  playerMf->setMesh(mesh);
}

void LayerScreen::onUpdate()
{
  playerGo->getComponent<Transform>()->rotate(Vector3(0, 100, 0) * Time::getDeltaTime());
}

void LayerScreen::onGui()
{
  if(Gui::button(Rect(Screen::getWidth() - 210, 10, 200, 50), "Back") == true)
  {
    Application::loadLevel("introduction");
  }

  Gui::label(Rect(10, 10, 100, 30), "Model Layer");

  if(Gui::button(Rect(10, 50, 100, 30), "Zero") == true)
  {
    playerGo->setLayer(1 << 0);
  }

  if(Gui::button(Rect(10, 90, 100, 30), "One") == true)
  {
    playerGo->setLayer(1 << 1);
  }

  Gui::label(Rect(10, 130, 150, 30), "Camera Cull Mask");

  if(Gui::button(Rect(10, 170, 100, 30), "Zero") == true)
  {
    // Display only layer 0
    cameraGo->getComponent<Camera>()->setCullMask(1 << 0);
  }

  if(Gui::button(Rect(10, 210, 100, 30), "One") == true)
  {
    // Display only layer 1
    cameraGo->getComponent<Camera>()->setCullMask(1 << 1);
  }

  if(Gui::button(Rect(10, 250, 100, 30), "Not One") == true)
  {
    // Display only layer 1
    int cullMask = 1 << 1;

    // Display everything but layer 1
    cullMask = ~cullMask;

    cameraGo->getComponent<Camera>()->setCullMask(cullMask);
  }
}

