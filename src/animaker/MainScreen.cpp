#include "MainScreen.h"
#include "MainCamera.h"
#include "Timeline.h"
#include "menus/SelectModelScreen.h"

using namespace mutiny::engine;

void MainScreen::onAwake()
{
  MainCamera::create();

  root = new GameObject("root");

  GameObject* go = new GameObject();
  MeshFilter* mf = go->addComponent<MeshFilter>();
  mf->setMesh(Resources::load<Mesh>(SelectModelScreen::choice.substr(0, SelectModelScreen::choice.length() - 4)));
  MeshRenderer* mr = go->addComponent<MeshRenderer>();

  Material* material = Resources::load<Material>("shaders/textured");
  material->setMainTexture(Resources::load<Texture2d>("models/curuthers/Whiskers_diffuse"));
  mr->setMaterial(material);

  go->getTransform()->setParent(root->getTransform());
  root->getTransform()->rotate(Vector3(0, 180, 0));

  Timeline::create();
}

void MainScreen::onUpdate()
{
  Vector3 mousePosition = Input::getMousePosition();
  Vector3 mouseDelta = mousePosition - lastMousePosition;
  lastMousePosition = Vector2(mousePosition.x, mousePosition.y);

  //std::cout << mouseDelta.x << mouseDelta.y << mouseDelta.z << std::endl;

  //root->getTransform()->rotate(Vector3(0, 100, 0) * Time::getDeltaTime());

  if(Input::getMouseButton(1) == true)
  {
    //root->getTransform()->rotate(Vector3(mouseDelta.y, -mouseDelta.x, 0));
    root->getTransform()->rotate(Vector3(0, -mouseDelta.x, 0));
  }
}

void MainScreen::onGui()
{
  if(Gui::button(Rect(10, 10, 100, 30), "back") == true)
  {
    Application::loadLevel("Menu");
  }
}

