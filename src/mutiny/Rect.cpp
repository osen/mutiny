#include "Rect.h"
#include "Vector3.h"

namespace mutiny
{

namespace engine
{

Rect::Rect(int x, int y, int width, int height)
{
  this->x = x;
  this->y = y;
  this->width = width;
  this->height = height;
}

bool Rect::contains(Vector3 point)
{
  if(point.y < y ||
     point.x < x ||
     point.x > x + width ||
     point.y > y + height)
  {
    return false;
  }

  return true;
}

}

}

