#ifndef MUTINY_ENGINE_GAMEOBJECT_H
#define MUTINY_ENGINE_GAMEOBJECT_H

#include "Component.h"
#include "Application.h"

#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>

namespace mutiny
{

namespace engine
{

class Component;
class Transform;
class Collision;
class RidgedBody;

class GameObject : public Object
{
  friend class mutiny::engine::Application;
  friend class mutiny::engine::RidgedBody;

public:
  static ref<GameObject> createPrimitive(int primitiveType);
  static ref<GameObject> createModel(std::string path);

  template<class T> static std::vector<ref<T> > findObjectsOfType()
  {
    std::vector<shared<GameObject> >& gameObjects = Application::getGameObjects();
    std::vector<ref<T> > objects;

    for(int i = 0; i < gameObjects.size(); i++)
    {
      ref<GameObject> gameObject = gameObjects.at(i);

      ref<T> testGameObject =
        dynamic_cast<T*>(gameObject.get());

      if(testGameObject.valid())
      {
        objects.push_back(testGameObject);
      }

      ref<T> testComponent =
        dynamic_cast<T*>(gameObject->getComponent<T>().try_get());

      if(testComponent.valid())
      {
        objects.push_back(testComponent);
      }
    }

    return objects;
  }

  static void findGameObjectsWithTag(std::string tag, std::vector<ref<GameObject> >& gameObjects);
  static ref<GameObject> create();
  static ref<GameObject> create(std::string name);

  GameObject();
  GameObject(std::string name);
  GameObject(int dummy);
  ~GameObject();

  void setActive(bool active);
  bool getActive();
  bool getActiveSelf();
  int getLayer();
  void setLayer(int layer);
  ref<Transform> getTransform();
  void setTag(std::string tag);
  std::string getTag();

  template <class T>
  ref<T> addComponent()
  {
    shared<T> c(new T());

    components.push_back(c);
    c->gameObject = this;
    c->awake();

    return c;
  }

  template<class T>
  ref<T> getComponent()
  {
    for(int i = 0; i < components.size(); i++)
    {
      ref<T> t = dynamic_cast<T*>(components.at(i).get());

      if(t.valid())
      {
        return t;
      }
    }

    return ref<T>();
  }

private:
  std::vector<shared<Component> > components;
  bool activeSelf;
  int layer;
  std::string tag;

  virtual void awake();
  virtual void start();
  virtual void update();
  virtual void render();
  virtual void postRender();
  virtual void gui();
  virtual void destroy();
  virtual void levelWasLoaded();
  virtual void collisionEnter(Collision& collision);
  virtual void collisionStay(Collision& collision);
  virtual void collisionExit(Collision& collision);

};

}

}

#endif

