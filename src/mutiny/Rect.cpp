#include "Rect.h"
#include "Vector3.h"
#include "Vector2.h"

namespace mutiny
{

namespace engine
{

Rect::Rect()
{
  x = 0;
  y = 0;
  width = 0;
  height = 0;
}

Rect::Rect(Vector2 position, Vector2 size)
{
  this->x = position.x;
  this->y = position.y;
  this->width = size.x;
  this->height = size.y;
}

Rect::Rect(float x, float y, float width, float height)
{
  this->x = x;
  this->y = y;
  this->width = width;
  this->height = height;
}

bool Rect::contains(Vector2 point)
{
  return contains(Vector3(point.x, point.y, 0));
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

