#ifndef MUTINY_ENGINE_BOUNDS_H
#define MUTINY_ENGINE_BOUNDS_H

#include "Vector3.h"

namespace mutiny
{

namespace engine
{

class Bounds
{
public:
  Vector3 center;
  Vector3 size;
  Vector3 extents;
  Vector3 min;
  Vector3 max;

  Bounds();
  Bounds(Vector3 center, Vector3 size);

  bool intersects(Bounds target);
  void setMinMax(Vector3 min, Vector3 max);

  void debug();

};

}

}

#endif

