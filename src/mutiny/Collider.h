#ifndef MUTINY_ENGINE_COLLIDER_H
#define MUTINY_ENGINE_COLLIDER_H

#include "Behaviour.h"
#include "Bounds.h"

namespace mutiny
{

namespace engine
{

class Mesh;
class GameObject;

class Collider : public Component
{
  friend class mutiny::engine::GameObject;

public:
  Collider();
  virtual ~Collider();

  Bounds getBounds();

protected:
  Bounds bounds;
  Vector3 lastPosition;

  virtual void awake();
  virtual void update();

private:
  void updateBounds();

};

}

}

#endif

