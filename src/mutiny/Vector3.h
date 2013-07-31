#ifndef MUTINY_ENGINE_VECTOR3_H
#define MUTINY_ENGINE_VECTOR3_H

namespace mutiny
{

namespace engine
{

class Vector2;
class Vector3
{
public:
  float x;
  float y;
  float z;

  Vector3();
  Vector3(float x, float y);
  Vector3(float x, float y, float z);

  Vector3 operator-(Vector2 param);
  Vector3 operator-(Vector3 param);
  Vector3 operator+(Vector3 param);
  Vector3 operator*(Vector3 param);
  Vector3 operator/(float param);
  Vector3 operator*(float param);
  Vector3 operator+(float param);

  Vector3 getNormalized();

};

}

}

#endif

