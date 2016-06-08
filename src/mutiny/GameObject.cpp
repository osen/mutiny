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

ref<GameObject> GameObject::createPrimitive(int primitiveType)
{
  ref<GameObject> gameObject = GameObject::create();

  ref<MeshFilter> meshFilter = gameObject->addComponent<MeshFilter>();
  meshFilter->setMesh(Resources::load<Mesh>("primitives/cube"));

  ref<MeshRenderer> meshRenderer = gameObject->addComponent<MeshRenderer>();
  //meshRenderer->setMaterial(material);

  return gameObject;
}

ref<GameObject> GameObject::createModel(std::string path)
{
  // TODO: Do we really want to be creating an AnimatedMesh?
  // I have only done this because it does much of the work for me
  // rather than manually loading textures per material group etc...
  ref<GameObject> gameObject = GameObject::create();

  ref<AnimatedMeshRenderer> amr = gameObject->addComponent<AnimatedMeshRenderer>();
  ref<AnimatedMesh> mesh = Resources::load<AnimatedMesh>(path);
  amr->setAnimatedMesh(mesh);

  for(size_t i = 0; i < amr->getRoot()->getTransform()->getChildCount(); i++)
  {
    amr->getRoot()->getTransform()->getChild(i)->getGameObject()->addComponent<MeshCollider>();
  }

  return gameObject;
}

GameObject::GameObject(std::string name)
{
  setName(name);
  addComponent<Transform>();
  Application::getGameObjects().push_back(shared<GameObject>(this));
  activeSelf = true;
  layer = 1 << 0;
}

GameObject::GameObject()
{
  addComponent<Transform>();
  Application::getGameObjects().push_back(shared<GameObject>(this));
  activeSelf = true;
  layer = 1 << 0;
}

ref<GameObject> GameObject::create(std::string name)
{
  ref<GameObject> rtn = create();
  rtn->name = name;

  return rtn;
}

ref<GameObject> GameObject::create()
{
  ref<GameObject> rtn;

  rtn = new GameObject();

  return rtn;
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
  for(size_t i = 0; i < components.size(); i++)
  {
    components.at(i)->awake();
  }
}

void GameObject::start()
{
  for(size_t i = 0; i < components.size(); i++)
  {
    components.at(i)->start();
  }
}

void GameObject::update()
{
  for(size_t i = 0; i < components.size(); i++)
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
  for(size_t i = 0; i < components.size(); i++)
  {
    components.at(i)->render();
  }
}

void GameObject::postRender()
{
  for(size_t i = 0; i < components.size(); i++)
  {
    components.at(i)->postRender();
  }
}

void GameObject::gui()
{
  for(size_t i = 0; i < components.size(); i++)
  {
    components.at(i)->gui();
  }
}

void GameObject::destroy()
{
  for(size_t i = 0; i < components.size(); i++)
  {
    components.at(i)->destroy();
  }
}

void GameObject::levelWasLoaded()
{
  for(size_t i = 0; i < components.size(); i++)
  {
    components.at(i)->levelWasLoaded();
  }
}

void GameObject::collisionEnter(Collision& collision)
{
  for(size_t i = 0; i < components.size(); i++)
    components.at(i)->collisionEnter(collision);
}

void GameObject::collisionStay(Collision& collision)
{
  for(size_t i = 0; i < components.size(); i++)
    components.at(i)->collisionStay(collision);
}

void GameObject::collisionExit(Collision& collision)
{
  for(size_t i = 0; i < components.size(); i++)
    components.at(i)->collisionExit(collision);
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

ref<Transform> GameObject::getTransform()
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

void GameObject::findGameObjectsWithTag(std::string tag, std::vector<ref<GameObject> >& gameObjects)
{
  std::vector<shared<GameObject> >& _gameObjects =
    Application::getGameObjects();

  for(size_t i = 0; i < _gameObjects.size(); i++)
  {
    if(_gameObjects.at(i)->getTag() == tag)
    {
      gameObjects.push_back(_gameObjects.at(i));
    }
  }
}

}

}

