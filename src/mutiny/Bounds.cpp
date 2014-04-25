#include "Bounds.h"
#include "Debug.h"

#include <sstream>
#include <iostream>

namespace mutiny
{

namespace engine
{

Bounds::Bounds()
{

}

Bounds::Bounds(Vector3 center, Vector3 size)
{
  this->center = center;
  this->size = size;
  this->extents = size / 2.0f;
  this->min = center - extents;
  this->max = center + extents;
}

void Bounds::setMinMax(Vector3 min, Vector3 max)
{
  center = (min + max) / 2.0f;
  extents = max - center;
  size = extents * 2.0f;
  this->min = center - extents;
  this->max = center + extents;
}

void Bounds::debug()
{
  std::cout << "Center: " << center.x << " " << center.y << " " << center.z << std::endl;
  std::cout << "Size: " << size.x << " " << size.y << " " << size.z << std::endl;
  std::cout << "Extents: " << extents.x << " " << extents.y << " " << extents.z << std::endl;
  std::cout << "Min: " << min.x << " " << min.y << " " << min.z << std::endl;
  std::cout << "Max: " << max.x << " " << max.y << " " << max.z << std::endl;
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

