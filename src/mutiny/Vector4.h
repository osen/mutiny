#ifndef MUTINY_ENGINE_VECTOR4_H
#define MUTINY_ENGINE_VECTOR4_H

namespace mutiny
{

namespace engine
{

class Vector2;
class Vector4
{
public:
  float x;
  float y;
  float z;
  float w;

  Vector4();
  Vector4(float val);
  Vector4(float x, float y);
  Vector4(float x, float y, float z, float w);

  Vector4 operator-(Vector2 param);
  Vector4 operator-(Vector4 param);
  Vector4 operator+(Vector4 param);
  Vector4 operator*(Vector4 param);
  Vector4 operator/(float param);
  Vector4 operator*(float param);
  Vector4 operator+(float param);

  float getMagnitude();
  Vector4 getNormalized();
  static float getDistance(Vector4 a, Vector4 b);

};

}

}

#endif

