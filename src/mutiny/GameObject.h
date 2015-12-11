#ifndef MUTINY_ENGINE_GAMEOBJECT_H
#define MUTINY_ENGINE_GAMEOBJECT_H

#include "Component.h"
#include "Application.h"
#include "arc.h"

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

class GameObject : public Object
{
  friend class Application;

public:
  static GameObject* createPrimitive(int primitiveType);
  static GameObject* createModel(std::string path);

  template<class T> static std::vector<Object*> findObjectsOfType()
  {
    std::vector<Object*> objects;

    for(int i = 0; i < Application::gameObjects.size(); i++)
    {
      void* gameObject =
        dynamic_cast<T*>(Application::gameObjects.at(i).get());

      if(gameObject != NULL)
      {
        objects.push_back((Object*)gameObject);
      }

      void* component =
        dynamic_cast<T*>(Application::gameObjects.at(i)->getComponent<T>());

      if(component != NULL)
      {
        objects.push_back((Object*)component);
      }
    }

    return objects;
  }

  static void findGameObjectsWithTag(std::string tag, std::vector<GameObject*>* gameObjects);
  static arc<GameObject> create();
  static arc<GameObject> create(std::string name);

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

  template<class T>
  arc<Component> castToComponent()
  {
    arc<GameObject> g;
    arc<Object> c = g.cast<Object>();
    return arc<Component>();
  }

  template<class T> T* addComponent()
  {
    T* tm = (T*)calloc(1, sizeof(*tm));

    if(tm == NULL)
    {
      throw std::exception();
    }

    T* t = new(tm) T();

    if(t == NULL)
    {
      free(tm);
      throw std::exception();
    }

    arc<Component> c = arc<Component>::placement_alloc(t);

    components.push_back(c);
    c->gameObject = this;
    c->awake();

    return (T*)c.get();
  }

  template<class T> T* getComponent()
  {
    for(int i = 0; i < components.size(); i++)
    {
      T* t = dynamic_cast<T*>(components.at(i).get());

      if(t != NULL)
      {
        return (T*)components.at(i).get();
      }
    }

    return NULL;
  }

private:
  std::vector<arc<Component> > components;
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

};

}

}

#endif

