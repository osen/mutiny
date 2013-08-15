#include "MainScreen.h"
#include "MainCamera.h"
#include "Timeline.h"
#include "menus/SelectModelScreen.h"

using namespace mutiny::engine;

void MainScreen::onAwake()
{
  MainCamera::create();

  root = new GameObject("root");
  animationGo = new GameObject();

  animatedMesh = Resources::load<AnimatedMesh>(SelectModelScreen::choice.substr(0, SelectModelScreen::choice.length() - 4));

  if(animatedMesh == NULL)
  {
    Debug::log("Mesh is null :(");
  }

  AnimatedMeshRenderer* amr = animationGo->addComponent<AnimatedMeshRenderer>();
  amr->setAnimatedMesh(animatedMesh);

  animationGo->getTransform()->setParent(root->getTransform());
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

  Transform* rootTransform = animationGo->getTransform()->find("root");

  if(rootTransform == NULL)
  {
    return;
  }

  for(int i = 0; i < rootTransform->getChildCount(); i++)
  {
    Gui::label(Rect(100, 100 + (20 * i), 100, 100), rootTransform->getChild(i)->getGameObject()->getName());
  }
}

