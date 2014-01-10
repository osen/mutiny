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
  LayerCamera::create();
  GameObject* playerGo = new GameObject("Player");
  playerGo->getTransform()->setPosition(Vector3(0, 0, 0));

  MeshRenderer* playerMr = playerGo->addComponent<MeshRenderer>();
  playerMr->setMaterial(Resources::load<Material>("shaders/textured"));
  playerMr->getMaterial()->setMainTexture(Resources::load<Texture2d>("models/curuthers/Whiskers_diffuse"));

  Mesh* mesh = Resources::load<Mesh>("models/curuthers/curuthers");
  MeshFilter* playerMf = playerGo->addComponent<MeshFilter>();
  playerMf->setMesh(mesh);
  
  
}

void LayerScreen::onGui()
{
  if(Gui::button(Rect(Screen::getWidth() - 210, 10, 200, 50), "Back") == true)
  {
    Application::loadLevel("introduction");
  }
}

