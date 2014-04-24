#include "GameObject.h"
#include "Application.h"
#include "MeshFilter.h"
#include "MeshRenderer.h"
#include "Mesh.h"
#include "Resources.h"
#include "Transform.h"
#include "Debug.h"

#include "MeshCollider.h"
#include "buccaneer/buccaneer.h"

namespace mutiny
{

namespace engine
{

GameObject* GameObject::createPrimitive(int primitiveType)
{
  GameObject* gameObject = new GameObject();

  MeshFilter* meshFilter = gameObject->addComponent<MeshFilter>();
  meshFilter->setMesh(Resources::load<Mesh>("primitives/cube"));

  MeshRenderer* meshRenderer = gameObject->addComponent<MeshRenderer>();
  //meshRenderer->setMaterial(material);

  return gameObject;
}

GameObject* GameObject::createModel(std::string path)
{
  // TODO: Do we really want to be creating an AnimatedMesh?
  // I have only done this because it does much of the work for me
  // rather than manually loading textures per material group etc...
  GameObject* gameObject = new GameObject();

  AnimatedMeshRenderer* amr = gameObject->addComponent<AnimatedMeshRenderer>();
  AnimatedMesh* mesh = Resources::load<AnimatedMesh>(path);
  amr->setAnimatedMesh(mesh);

  for(int i = 0; i < amr->getRoot()->getTransform()->getChildCount(); i++)
  {
    amr->getRoot()->getTransform()->getChild(i)->getGameObject()->addComponent<MeshCollider>();
  }

  return gameObject;
}

GameObject::GameObject(std::string name)
{
  setName(name);
  addComponent<Transform>();
  Application::gameObjects.push_back(std::shared_ptr<GameObject>(this));
  activeSelf = true;
  layer = 1 << 0;
}

GameObject::GameObject()
{
  addComponent<Transform>();
  Application::gameObjects.push_back(std::shared_ptr<GameObject>(this));
  activeSelf = true;
  layer = 1 << 0;
}

GameObject::~GameObject()
{

}

void GameObject::setLayer(int layer)
{
  this->layer = layer;
}

int GameObject::getLayer()
{
  return layer;
}

void GameObject::awake()
{
  for(int i = 0; i < components.size(); i++)
  {
    components.at(i)->awake();
  }
}

void GameObject::start()
{
  for(int i = 0; i < components.size(); i++)
  {
    components.at(i)->start();
  }
}

void GameObject::update()
{
  for(int i = 0; i < components.size(); i++)
  {
    if(components.at(i)->destroyed == true)
    {
      components.at(i)->destroy();
      components.erase(components.begin() + i);
      i--;
    }
    else
    {
      components.at(i)->update();
    }
  }
}

void GameObject::render()
{
  for(int i = 0; i < components.size(); i++)
  {
    components.at(i)->render();
  }
}

void GameObject::postRender()
{
  for(int i = 0; i < components.size(); i++)
  {
    components.at(i)->postRender();
  }
}

void GameObject::gui()
{
  for(int i = 0; i < components.size(); i++)
  {
    components.at(i)->gui();
  }
}

void GameObject::destroy()
{
  for(int i = 0; i < components.size(); i++)
  {
    components.at(i)->destroy();
  }
}

void GameObject::levelWasLoaded()
{
  for(int i = 0; i < components.size(); i++)
  {
    components.at(i)->levelWasLoaded();
  }
}

void GameObject::setActive(bool active)
{
  this->activeSelf = active;
}

bool GameObject::getActiveSelf()
{
  return activeSelf;
}

bool GameObject::getActive()
{
  // TODO: check that each parent of each transform is active.
  return activeSelf;
}

Transform* GameObject::getTransform()
{
  return getComponent<Transform>();
}

std::string GameObject::getTag()
{
  return tag;
}

void GameObject::setTag(std::string tag)
{
  this->tag = tag;
}

void GameObject::findGameObjectsWithTag(std::string tag, std::vector<GameObject*>* gameObjects)
{
  for(int i = 0; i < Application::gameObjects.size(); i++)
  {
    if(Application::gameObjects.at(i)->getTag() == tag)
    {
      gameObjects->push_back(Application::gameObjects.at(i).get());
    }
  }
}

}

}

