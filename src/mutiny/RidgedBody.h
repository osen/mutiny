#ifndef MUTINY_ENGINE_RIDGEDBODY_H
#define MUTINY_ENGINE_RIDGEDBODY_H

#include "Behaviour.h"
#include "Collision.h"

#include <vector>

namespace mutiny
{

namespace engine
{

class Vector3;

class RidgedBody : public Component
{
public:
  RidgedBody();
  virtual ~RidgedBody();

private:
  virtual void update();

  bool colliding(Vector3& center, Vector3& half, Vector3& a, Vector3& b, Vector3& c);

  std::vector<Collision> collisions;

};

}

}

#endif

