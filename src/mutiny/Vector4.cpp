#include "Vector4.h"
#include "Vector2.h"

#include <cmath>

namespace mutiny
{

namespace engine
{

Vector4::Vector4()
{
  x = 0;
  y = 0;
  z = 0;
  w = 0;
}

Vector4::Vector4(float val)
{
  x = val;
  y = val;
  z = val;
  w = val;
}

Vector4::Vector4(float x, float y)
{
  this->x = x;
  this->y = y;
  this->z = 0;
  this->w = 0;
}

Vector4::Vector4(float x, float y, float z, float w)
{
  this->x = x;
  this->y = y;
  this->z = z;
  this->w = w;
}

Vector4 Vector4::operator*(Vector4 param)
{
  return Vector4(x * param.x, y * param.y, z * param.z, w * param.w);
}

Vector4 Vector4::operator+(Vector4 param)
{
  return Vector4(x + param.x, y + param.y, z + param.z, w + param.w);
}

Vector4 Vector4::operator-(Vector4 param)
{
  return Vector4(x - param.x, y - param.y, z - param.z, w - param.w);
}

Vector4 Vector4::operator-(Vector2 param)
{
  return Vector4(x - param.x, y - param.y, z, w);
}

Vector4 Vector4::operator*(float param)
{
  return Vector4(x * param, y * param, z * param, w * param);
}

Vector4 Vector4::operator+(float param)
{
  return Vector4(x + param, y + param, z + param, w + param);
}

Vector4 Vector4::operator/(float param)
{
  return Vector4(x / param, y / param, z / param, w / param);
}

Vector4 Vector4::getNormalized()
{
  Vector4 rtn;
  float length = sqrt(x*x+y*y+z*z+w*w);

  rtn.x = x/length;
  rtn.y = y/length;
  rtn.z = z/length;
  rtn.w = w/length;

  return rtn;
}

float Vector4::getMagnitude()
{
  return sqrt(x*x+y*y+z*z+w*w);
}

float Vector4::getDistance(Vector4 a, Vector4 b)
{
  return (a - b).getMagnitude();
}

}

}

