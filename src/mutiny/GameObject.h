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
  static GameObject* createPrimitive(int primitiveType);
  static GameObject* createModel(std::string path);

  template<class T> static std::vector<Object*> findObjectsOfType()
  {
    internal::gc::list<GameObject*>* gameObjects = Application::getGameObjects();
    std::vector<Object*> objects;

    for(int i = 0; i < gameObjects->size(); i++)
    {
      void* gameObject =
        dynamic_cast<T*>(gameObjects->at(i));

      if(gameObject != NULL)
      {
        objects.push_back((Object*)gameObject);
      }

      void* component =
        dynamic_cast<T*>(gameObjects->at(i)->getComponent<T>());

      if(component != NULL)
      {
        objects.push_back((Object*)component);
      }
    }

    return objects;
  }

  static void findGameObjectsWithTag(std::string tag, std::vector<GameObject*>* gameObjects);
  static GameObject* create();
  static GameObject* create(std::string name);

  GameObject();
  GameObject(std::string name);
  GameObject(int dummy);
  ~GameObject();

  void setActive(bool active);
  bool getActive();
  bool getActiveSelf();
  int getLayer();
  void setLayer(int layer);
  Transform* getTransform();
  void setTag(std::string tag);
  std::string getTag();

  template <class T>
  T* addComponent()
  {
    T* c = Application::getGC()->gc_new<T>();

    components->push_back(c);
    c->gameObject = this;
    c->awake();

    return c;
  }

  template<class T>
  T* getComponent()
  {
    for(int i = 0; i < components->size(); i++)
    {
      T* t = dynamic_cast<T*>(components->at(i));

      if(t != NULL)
      {
        return t;
      }
    }

    return NULL;
  }

private:
  internal::gc::list<Component*>* components;
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

