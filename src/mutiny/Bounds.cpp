#include "Bounds.h"
#include "Debug.h"

#include <sstream>

namespace mutiny
{

namespace engine
{

Bounds::Bounds(Vector3 center, Vector3 size)
{
  this->center = center;
  this->size = size;
  this->extents = size / 2.0f;
  this->min = center - extents;
  this->max = center + extents;
}

bool Bounds::intersects(Bounds target)
{
  bool collidingX = false;
  bool collidingY = false;
  bool collidingZ = false;

  if(min.x < target.min.x)
  {
    if(max.x >= target.min.x)
    {
      collidingX = true;
    }
  }
  else
  {
    if(target.max.x >= min.x)
    {
      collidingX = true;
    }
  }

  if(min.y < target.min.y)
  {
    if(max.y >= target.min.y)
    {
      collidingY = true;
    }
  }
  else
  {
    if(target.max.y >= min.y)
    {
      collidingY = true;
    }
  }

  if(min.z < target.min.z)
  {
    if(max.z >= target.min.z)
    {
      collidingZ = true;
    }
  }
  else
  {
    if(target.max.z >= min.z)
    {
      collidingZ = true;
    }
  }

  if(collidingX == true && collidingY == true && collidingZ == true)
  {
    return true;
  }

  return false;
}

}

}

