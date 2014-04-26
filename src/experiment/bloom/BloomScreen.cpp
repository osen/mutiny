#include "BloomScreen.h"
#include "BloomCamera.h"

using namespace mutiny::engine;

GameObject* BloomScreen::create()
{
  GameObject* mainGo = new GameObject("BloomScreen");
  mainGo->addComponent<BloomScreen>();

  return mainGo;
}

void BloomScreen::onAwake()
{
  BloomCamera::create();
  GameObject* playerGo = new GameObject("Player");
  playerGo->getTransform()->setPosition(Vector3(-10, 0, -10));

  MeshRenderer* playerMr = playerGo->addComponent<MeshRenderer>();
  playerMr->setMaterial(Resources::load<Material>("shaders/textured"));
  playerMr->getMaterial()->setMainTexture(Resources::load<Texture2d>("models/curuthers/Whiskers_diffuse"));

  Mesh* mesh = Resources::load<Mesh>("models/curuthers/curuthers");
  MeshFilter* playerMf = playerGo->addComponent<MeshFilter>();
  playerMf->setMesh(mesh);
  
  
}

void BloomScreen::onGui()
{
  if(Gui::button(Rect(Screen::getWidth() - 210, 10, 200, 50), "Back") == true)
  {
    Application::loadLevel("introduction");
  }
}

