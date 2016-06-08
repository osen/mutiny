#ifndef MUTINY_ENGINE_CONTACTPOINT_H
#define MUTINY_ENGINE_CONTACTPOINT_H

#include "Vector3.h"

namespace mutiny
{

namespace engine
{

class Collider;

class ContactPoint
{
public:
  Vector3 point;
  Vector3 normal;
  ref<Collider> thisCollider;
  ref<Collider> otherCollider;
  Vector3 a;
  Vector3 b;
  Vector3 c;

};

}

}

#endif

