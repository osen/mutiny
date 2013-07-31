#include "Vector2.h"

namespace mutiny
{

namespace engine
{

Vector2::Vector2()
{
  x = 0;
  y = 0;
}

Vector2::Vector2(float x, float y)
{
  this->x = x;
  this->y = y;
}

Vector2 Vector2::operator-(Vector2 param)
{
  return Vector2(x - param.x, y - param.y);
}

}

}

