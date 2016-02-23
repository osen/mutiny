#include "BloomScreen.h"
#include "BloomCamera.h"

using namespace mutiny::engine;

GameObject* BloomScreen::create()
{
  GameObject* mainGo = GameObject::create("BloomScreen");
  mainGo->addComponent<BloomScreen>();

  return mainGo;
}

void BloomScreen::onAwake()
{
  BloomCamera::create();
  playerGo = GameObject::create("Player");
  playerGo->getTransform()->setPosition(Vector3(-10, 0, -10));

  MeshRenderer* playerMr = playerGo->addComponent<MeshRenderer>();
  playerMr->setMaterial(Resources::load<Material>("shaders/Internal-MeshRendererTexture"));
  playerMr->getMaterial()->setMainTexture(Resources::load<Texture2d>("models/curuthers/Whiskers_diffuse"));

  Mesh* mesh = Resources::load<Mesh>("models/curuthers/curuthers");
  MeshFilter* playerMf = playerGo->addComponent<MeshFilter>();
  playerMf->setMesh(mesh);
}

void BloomScreen::onUpdate()
{
  playerGo->getComponent<Transform>()->rotate(Vector3(0, -100, 0) * Time::getDeltaTime());
}

void BloomScreen::onGui()
{
  if(Gui::button(Rect(Screen::getWidth() - 210, 10, 200, 50), "Back") == true)
  {
    Application::loadLevel("introduction");
  }
}

