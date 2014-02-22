#ifndef MUTINY_ENGINE_GAMEOBJECT_H
#define MUTINY_ENGINE_GAMEOBJECT_H

#include "Component.h"
#include "Application.h"

#include "internal/Internal.h"

#include <memory>

#include <string>
#include <vector>
#include <iostream>

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

    for(int i = 0; i < Application::getInternal()->gameObjects.size(); i++)
    {
      Component* component = Application::getInternal()->gameObjects.at(i)->getComponent<T>();

      if(component != NULL)
      {
        objects.push_back((Object*)Application::getInternal()->gameObjects.at(i).get());
      }
    }

    return objects;
  }

  static void findGameObjectsWithTag(std::string tag, std::vector<GameObject*>* gameObjects);

  GameObject();
  GameObject(std::string name);
  ~GameObject();

  void setActive(bool active);
  bool getActive();
  bool getActiveSelf();
  int getLayer();
  void setLayer(int layer);
  Transform* getTransform();
  void setTag(std::string tag);
  std::string getTag();

  template<class T> T* addComponent()
  {
    T* t = new T();

    components.push_back(std::shared_ptr<Component>(t));
    t->gameObject = this;
    t->awake();

    return t;
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
  std::vector<std::shared_ptr<Component> > components;
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

