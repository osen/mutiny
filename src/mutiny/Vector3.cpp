#include "Vector3.h"

#include <cmath>

namespace mutiny
{

namespace engine
{

Vector3::Vector3()
{
  x = 0;
  y = 0;
  z = 0;
}

Vector3::Vector3(float x, float y)
{
  this->x = x;
  this->y = y;
  this->z = 0;
}

Vector3::Vector3(float x, float y, float z)
{
  this->x = x;
  this->y = y;
  this->z = z;
}

Vector3 Vector3::operator*(Vector3 param)
{
  return Vector3(x * param.x, y * param.y, z * param.z);
}

Vector3 Vector3::operator+(Vector3 param)
{
  return Vector3(x + param.x, y + param.y, z + param.z);
}

Vector3 Vector3::operator-(Vector3 param)
{
  return Vector3(x - param.x, y - param.y, z - param.z);
}

Vector3 Vector3::operator*(float param)
{
  return Vector3(x * param, y * param, z * param);
}

Vector3 Vector3::operator+(float param)
{
  return Vector3(x + param, y + param, z + param);
}

Vector3 Vector3::operator/(float param)
{
  return Vector3(x / param, y / param, z / param);
}

Vector3 Vector3::getNormalized()
{
  Vector3 rtn;
  float length = sqrt(x*x+y*y+z*z);

  rtn.x = x/length;
  rtn.y = y/length;
  rtn.z = z/length;

  return rtn;
}

}

}

