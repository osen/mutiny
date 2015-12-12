#ifndef MUTINY_ENGINE_COMPONENT_H
#define MUTINY_ENGINE_COMPONENT_H

#include "Object.h"

namespace mutiny
{

namespace engine
{

class GameObject;
class Application;
class Collision;

class Component : public Object
{
  friend class GameObject;
  friend class Application;

public:
  virtual ~Component();

  GameObject* getGameObject();

private:
  GameObject* gameObject;

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

