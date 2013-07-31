#include "MainScreen.h"
#include "MainCamera.h"
#include "menus/SelectModelScreen.h"

using namespace mutiny::engine;

void MainScreen::onAwake()
{
  MainCamera::create();

  root = new GameObject("root");

  GameObject* go = new GameObject();
  MeshFilter* mf = go->addComponent<MeshFilter>();
  //mf->setMesh(Resources::load<Mesh>("models/curuthers/curuthers"));
  mf->setMesh(Resources::load<Mesh>(SelectModelScreen::choice.substr(0, SelectModelScreen::choice.length() - 4)));
  MeshRenderer* mr = go->addComponent<MeshRenderer>();

  Material* material = Resources::load<Material>("shaders/textured");
  material->setMainTexture(Resources::load<Texture2d>("models/curuthers/Whiskers_diffuse"));
  mr->setMaterial(material);

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
  if(Gui::button(Rect(10, 10, 100, 30), "back") == true)
  {
    Application::loadLevel("SelectModel");
  }
}

