#include "MainScreen.h"
#include "MainCamera.h"

using namespace mutiny::engine;

void MainScreen::onAwake()
{
  MainCamera::create();

  root = new GameObject("root");

  GameObject* go = new GameObject();
  MeshFilter* mf = go->addComponent<MeshFilter>();
  mf->setMesh(Resources::load<Mesh>("models/curuthers/curuthers"));
  MeshRenderer* mr = go->addComponent<MeshRenderer>();
  //mr->setTexture(Resources::load<Texture2d>("models/curuthers/Whiskers_diffuse");

  Shader* shader = Resources::load<Shader>("shaders/textured");

  transient = GameObject::createPrimitive(PrimitiveType::CUBE);
  transient->getTransform()->setPosition(Vector3(1, 1, 1));
  transient2 = GameObject::createPrimitive(PrimitiveType::CUBE);
  transient2->getTransform()->setPosition(Vector3(1, 1, 1));

  transient2->getTransform()->setParent(root->getTransform());
  transient->getTransform()->setParent(transient2->getTransform());
  go->getTransform()->setParent(transient->getTransform());

  simpleTex = new Texture2d(1, 1);
  simpleTex->setPixel(0, 0, Color(1, 0, 0));
  simpleTex->apply();
}

void MainScreen::onUpdate()
{
  transient2->getTransform()->rotate(Vector3(100, 100, 0) * Time::getDeltaTime());
  transient->getTransform()->rotate(Vector3(100, 100, 0) * Time::getDeltaTime());
}

void MainScreen::onGui()
{
  Gui::drawTexture(Rect(100, 100, 100, 100), simpleTex);
}

