#include "AccumScreen.h"
#include "AccumCamera.h"

using namespace mutiny::engine;

GameObject* AccumScreen::create()
{
  GameObject* mainGo = new GameObject("AccumScreen");
  mainGo->addComponent<AccumScreen>();

  return mainGo;
}

void AccumScreen::onAwake()
{
  AccumCamera::create();
  playerGo = new GameObject("Player");
  playerGo->getTransform()->setPosition(Vector3(-10, 0, -10));

  MeshRenderer* playerMr = playerGo->addComponent<MeshRenderer>();
  playerMr->setMaterial(Resources::load<Material>("shaders/accum/full_red"));
  playerMr->getMaterial()->setMainTexture(Resources::load<Texture2d>("models/darth/darth"));

  Mesh* mesh = Resources::load<Mesh>("models/darth/darth");
  MeshFilter* playerMf = playerGo->addComponent<MeshFilter>();
  playerMf->setMesh(mesh);
}

void AccumScreen::onUpdate()
{
  playerGo->getComponent<Transform>()->rotate(Vector3(0, -100, 0) * Time::getDeltaTime());
}

void AccumScreen::onGui()
{
  if(Gui::button(Rect(Screen::getWidth() - 210, 10, 200, 50), "Back") == true)
  {
    Application::loadLevel("introduction");
  }
}

