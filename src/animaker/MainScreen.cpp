#include "MainScreen.h"
#include "MainCamera.h"
#include "Timeline.h"
#include "menus/SelectModelScreen.h"

using namespace mutiny::engine;

void MainScreen::onAwake()
{
  MainCamera::create();

  selectedPart = NULL;
  root = new GameObject("root");
  animationGo = new GameObject();

  animatedMesh = Resources::load<AnimatedMesh>(SelectModelScreen::choice.substr(0, SelectModelScreen::choice.length() - 4));

  if(animatedMesh == NULL)
  {
    Debug::log("Mesh is null :(");
  }

  selectedMaterial = Resources::load<Material>("shaders/selected");

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

  //if(selectedPart != NULL)
  //{
  //  MeshRenderer* mr = selectedPart->getComponent<MeshRenderer>();
  //  mr->setMaterial(selectedMaterial);
  //}
}

void MainScreen::selectPart(std::string partName)
{
  Transform* rootTransform = animationGo->getTransform()->find("root");

  if(rootTransform == NULL)
  {
    return;
  }

  for(int i = 0; i < rootTransform->getChildCount(); i++)
  {
    if(rootTransform->getChild(i)->getGameObject()->getName() == partName)
    {
      if(selectedPart != NULL)
      {
        selectedPart->getComponent<MeshRenderer>()->setMaterials(origMaterials);
      }

      selectedPart = rootTransform->getChild(i)->getGameObject();
      origMaterials.clear();
      selectedPart->getComponent<MeshRenderer>()->getMaterials(&origMaterials);

      std::vector<Material*> newMaterials;

      for(int x = 0; x < origMaterials.size(); x++)
      {
        newMaterials.push_back(selectedMaterial);
      }

      selectedPart->getComponent<MeshRenderer>()->setMaterials(newMaterials);
    }
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

  std::string selectedName;
  for(int i = 0; i < rootTransform->getChildCount(); i++)
  {
    Rect rect(100, 100 + (20 * i), 100, 20);
    Gui::label(rect, rootTransform->getChild(i)->getGameObject()->getName());

    if(rect.contains(Input::getMousePosition()) == true)
    {
      selectedName = rootTransform->getChild(i)->getGameObject()->getName();
    }
  }

  if(selectedName != "")
  {
    //Debug::log(selectedName);
    selectPart(selectedName);
  }
}

