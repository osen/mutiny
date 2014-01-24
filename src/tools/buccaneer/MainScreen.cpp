#include "MainScreen.h"
#include "MainCamera.h"
#include "Timeline.h"
#include "menus/SelectModelScreen.h"
#include "menus/SelectAnimationScreen.h"

using namespace mutiny::engine;

/******************************************************************************
 * onAwake
 *
 * Set initial data and ensure that the selected AnimatedMesh is loaded.
 * Create a root GameObject in which to attach the animation GameObject to.
 * Add the AnimatedMeshRender Component to the animation GameObject.
 ******************************************************************************/
void MainScreen::onAwake()
{
  MainCamera::create();

  // Vector2(Vector3))?
  lastMousePosition.x = Input::getMousePosition().x;
  lastMousePosition.y = Input::getMousePosition().y;

  transformMode = 0;
  changeMade = false;
  pulseAmount = 0;
  pulseDown = false;
  selectedPart = NULL;
  root = new GameObject("root");
  animationGo = new GameObject();
  fallbackTex.reset(new Texture2d(1, 1));
  fallbackTex->setPixel(0, 0, Color(0.0f, 0.5f, 1.0f));
  fallbackTex->apply();
  animatedMesh = Resources::load<AnimatedMesh>(SelectModelScreen::choice.substr(0, SelectModelScreen::choice.length() - 4));

  if(animatedMesh == NULL)
  {
    Debug::logError("Mesh is null :(");
    //TODO: Throw exception
  }

  selectedMaterial = Resources::load<Material>("shaders/selected");
  amr = animationGo->addComponent<AnimatedMeshRenderer>();
  amr->setAnimatedMesh(animatedMesh);
  animation = Resources::load<Animation>(SelectAnimationScreen::choice);
  animationPath = SelectAnimationScreen::choice;
  amr->setAnimation(animation);
  animationGo->getTransform()->setParent(root->getTransform());
  undoBuffer.push_back(animation->frames);
  timeline = Timeline::create(this);
}

/******************************************************************************
 * modifyTransform
 *
 * Translate and rotate the specified AnimationTransform. The translation and
 * rotation is based losely (45 degrees) on the direction that the camera is
 * facing.
 ******************************************************************************/
void MainScreen::modifyTransform(AnimationTransform* transform)
{
  float sensitivity = 0.01f;
  Transform* rootTransform = NULL;
  Vector3 mousePosition = Input::getMousePosition();
  Vector3 mouseDelta = mousePosition - lastMousePosition;

  rootTransform = root->getTransform();

  if(mouseDelta.x != 0 || mouseDelta.y != 0)
  {
    changeMade = true;
  }

  if(rootTransform->getRotation().y >= 90 - 45 && rootTransform->getRotation().y < 180 - 45)
  {
    if(transformMode == 0) transform->pZ -= mouseDelta.x * sensitivity;
    if(transformMode == 1) transform->rZ += mouseDelta.y;
  }
  else if(rootTransform->getRotation().y >= 180 - 45 && rootTransform->getRotation().y < 180 + 45)
  {
    if(transformMode == 0) transform->pX += mouseDelta.x * sensitivity;
    if(transformMode == 1) transform->rX -= mouseDelta.y;
  }
  else if(rootTransform->getRotation().y >= 180 + 45 && rootTransform->getRotation().y < 360 - 45)
  {
    if(transformMode == 0) transform->pZ += mouseDelta.x * sensitivity;
    if(transformMode == 1) transform->rZ -= mouseDelta.y;
  }
  else
  {
    if(transformMode == 0) transform->pX -= mouseDelta.x * sensitivity;
    if(transformMode == 1) transform->rX += mouseDelta.y;
  }

  if(transformMode == 0) transform->pY -= mouseDelta.y * sensitivity;
  if(transformMode == 1) transform->rY -= mouseDelta.x;
}

/******************************************************************************
 * onUpdate
 *
 * Ensure that the root Transform's rotation is within 0 and 360. If the right
 * mouse button is down, rotate the root Transform. If the middle mouse button
 * is down, modify the AnimationTransform in the current frame with the
 * currently selected part name or add the AnimationTransform if it cannot be
 * found. If the middle mouse is released and something has been modified then
 * push a copy of the current transforms onto the undo list.
 ******************************************************************************/
void MainScreen::onUpdate()
{
  Transform* rootTransform = NULL;
  Vector3 mousePosition = Input::getMousePosition();
  Vector3 mouseDelta = mousePosition - lastMousePosition;

  rootTransform = root->getTransform();

  if(rootTransform->getRotation().y >= 360.0f)
  {
    rootTransform->setRotation(Vector3(0, rootTransform->getRotation().y - 360, 0));
  }
  else if(rootTransform->getRotation().y < 0.0f)
  {
    rootTransform->setRotation(Vector3(0, 360 + rootTransform->getRotation().y, 0));
  }

  if(Input::getMouseButton(1) == true)
  {
    //root->getTransform()->rotate(Vector3(mouseDelta.y, -mouseDelta.x, 0));
    root->getTransform()->rotate(Vector3(0, -mouseDelta.x, 0));
  }
  else if(Input::getMouseButton(2) == true)
  {
    if(selectedPart != NULL)
    {
      bool found = false;
      for(int i = 0; i < animation->frames.at(amr->getFrame()).transforms.size(); i++)
      {
        if(animation->frames.at(amr->getFrame()).transforms.at(i).partName == selectedPart->getName())
        {
          found = true;
          modifyTransform(&animation->frames.at(amr->getFrame()).transforms.at(i));
        }
      }

      if(found == false)
      {
        AnimationTransform newTransform;
        newTransform.partName = selectedPart->getName();
        animation->frames.at(amr->getFrame()).transforms.push_back(newTransform);
      }
    }
  }
  else if(changeMade == true)
  {
    changeMade = false;
    undoBuffer.push_back(animation->frames);
  }

  //if(selectedPart != NULL)
  //{
  //  MeshRenderer* mr = selectedPart->getComponent<MeshRenderer>();
  //  mr->setMaterial(selectedMaterial);
  //}

  if(pulseDown == false) { pulseAmount += Time::getDeltaTime(); }
  if(pulseDown == true) { pulseAmount -= Time::getDeltaTime(); }

  if(pulseAmount > 1.0f) {pulseDown = true; pulseAmount = 1.0f; }
  if(pulseAmount < 0.0f) {pulseDown = false; pulseAmount = 0.0f; }

  for(int i = 0; i < newMaterials.size(); i++)
  {
    newMaterials.at(i)->setFloat("in_Pulse", pulseAmount);
  }

  lastMousePosition = Vector2(mousePosition.x, mousePosition.y);
}

/******************************************************************************
 * selectPart
 *
 * Based on the string specified, iterate through all the GameObjects attached
 * to the root GameObject to find one with the same name. If an existing part
 * is selected, reapply the backed up materials before storing the new part's
 * existing materials so that a red pulse shader material can be used in place.
 * Copy across the texture or use a default one from the original material to
 * maintain the parts texture in the new shader.
 ******************************************************************************/
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

      std::vector<Material*> _newMaterials;
      newMaterials.clear();

      for(int x = 0; x < origMaterials.size(); x++)
      {
        Material* newMaterial = new Material(Resources::load<Shader>("shaders/selected"));
        newMaterials.push_back(std::unique_ptr<Material>(newMaterial));

        if(origMaterials.at(x)->getMainTexture() != NULL)
        {
          newMaterial->setMainTexture(origMaterials.at(x)->getMainTexture());
        }
        else
        {
          newMaterial->setMainTexture(fallbackTex.get());
        }

        _newMaterials.push_back(newMaterial);
      }

      selectedPart->getComponent<MeshRenderer>()->setMaterials(_newMaterials);
    }
  }
}

/******************************************************************************
 * onGui
 *
 * Draw back button, undo button, play/stop button and a list of all the parts
 * attached to the root GameObject. If back button clicked, load the menu
 * scene. If play/stop button clicked then play or stop the animation.
 * Iterate through each GameObject in root and generate rectangles to test for
 * mouse clicks in order to change selected part.
 ******************************************************************************/
void MainScreen::onGui()
{
  if(Gui::button(Rect(10, 10, 100, 30), "back") == true)
  {
    Application::loadLevel("Menu");
  }

  if(Gui::button(Rect(30 + 200, 10, 100, 30), "Save") == true)
  {
    animation->save(animationPath);
  }

  if(undoBuffer.size() > 1)
  {
    if(Gui::button(Rect(120, 10, 100, 30), "Undo") == true)
    {
      animation->frames = undoBuffer.at(undoBuffer.size() - 2);
      undoBuffer.erase(undoBuffer.begin() + (undoBuffer.size() - 1));
      undoBuffer.erase(undoBuffer.begin() + (undoBuffer.size() - 1));
      undoBuffer.push_back(animation->frames);

      if(amr->getFrame() >= animation->frames.size())
      {
        amr->setFrame(animation->frames.size() - 1);
      }
    }
  }

  if(amr->isPlaying() == false)
  {
    if(Gui::button(Rect(10, 50, 100, 30), "Play") == true)
    {
      amr->play();
    }
  }
  else
  {
    if(Gui::button(Rect(10, 50, 100, 30), "Stop") == true)
    {
      amr->stop();
    }
  }

  if(transformMode == 0)
  {
    if(Gui::button(Rect(Screen::getWidth() - 10 - 100, 10, 100, 30), "Translate") == true)
    {
      transformMode = 1;
    }
  }
  else
  {
    if(Gui::button(Rect(Screen::getWidth() - 10 - 100, 10, 100, 30), "Rotate") == true)
    {
      transformMode = 0;
    }
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
    if(Input::getMouseButtonDown(0) == true)
    {
      selectPart(selectedName);
    }
  }
}

