#include "CollisionScreen.h"
#include "Player.h"
#include "FallingCube.h"
#include "SkyBox.h"

#include <iostream>

using namespace mutiny::engine;

GameObject* CollisionScreen::create()
{
  GameObject* mainGo = GameObject::create("CollisionScreen");
  mainGo->addComponent<CollisionScreen>();

  return mainGo;
}

void CollisionScreen::onAwake()
{
  arc<Material> levelMaterial;
  arc<Mesh> levelMesh;

  Camera* camera = NULL;
  cameraGo = GameObject::create("MainCamera");
  camera = cameraGo->addComponent<Camera>();
  cameraGo->getTransform()->translate(Vector3(0, 7.5, -20));
  //cameraGo->getTransform()->rotate(Vector3(-25, 0, 0));

  //renderTexture = new RenderTexture(Screen::getHeight() / 5, Screen::getWidth() / 5);
  renderTexture.reset(new RenderTexture(128, 128));
  camera->setTargetTexture(renderTexture);

  camera2Go = GameObject::create("SubCamera");
  camera = camera2Go->addComponent<Camera>();
  camera2Go->getTransform()->translate(Vector3(0, 7.5, -20));
  //camera2Go->getTransform()->rotate(Vector3(-25, 0, 0));

  SkyBox::create(cameraGo);

  levelMesh = Resources::load<Mesh>("models/level/level");
  levelMaterial = Resources::load<Material>("shaders/internal-mesh-normal-texture");
  levelTexture = Resources::load<Texture2d>("models/level/level").cast<Texture>();
  levelMaterial->setMainTexture(levelTexture);

  levelGo = GameObject::create("Level");
  levelGo->addComponent<MeshFilter>()->setMesh(levelMesh);
  levelGo->addComponent<MeshRenderer>()->setMaterial(levelMaterial);
  levelGo->addComponent<MeshCollider>();
  levelGo->getTransform()->translate(Vector3(-20, 0, 0));
  levelGo->getTransform()->rotate(Vector3(0, -5, -10));

  level2Go = GameObject::create("Level");
  level2Go->addComponent<MeshFilter>()->setMesh(levelMesh);
  level2Go->addComponent<MeshRenderer>()->setMaterial(levelMaterial);
  level2Go->addComponent<MeshCollider>();
  //level2Go->getTransform()->translate(Vector3(20, 0, 0));
  //level2Go->getTransform()->rotate(Vector3(0, -5, -10));

  playerGo = Player::create()->getGameObject();
  cubeGo = FallingCube::create()->getGameObject();
}

void CollisionScreen::onUpdate()
{
  Vector3 pos = cameraGo->getTransform()->getPosition();
  pos.x = playerGo->getTransform()->getPosition().x;
  cameraGo->getTransform()->setPosition(pos);
  camera2Go->getTransform()->setPosition(pos);

  level2Go->getTransform()->rotate(Vector3(0.0f, 0, 1.0f) * Time::getDeltaTime());
  //levelGo->getTransform()->rotate(Vector3(0.0f, 0, 1.0f) * Time::getDeltaTime());

  //if(Input::getMouseButtonUp(0) == true)
  //{
  //  Application::loadLevel("ShaderTest");
  //}

  //std::cout << Input::getMousePosition().x << " " << Input::getMousePosition().y << std::endl;
}

void CollisionScreen::onGui()
{
  //Gui::drawTexture(Rect(0, 0, Screen::getWidth(), Screen::getHeight()), renderTexture);
  Gui::drawTexture(Rect(100, 100, 200, 200), renderTexture.cast<Texture>());
  //Gui::drawTexture(Rect(0, 200, 100, 100), levelTexture);

  if(Gui::button(Rect(Screen::getWidth() - 210, 10, 200, 50), "Back") == true)
  {
    Application::loadLevel("introduction");
  }
}

