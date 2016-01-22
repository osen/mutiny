#ifndef MUTINY_ENGINE_VECTOR2_H
#define MUTINY_ENGINE_VECTOR2_H

namespace mutiny
{

namespace engine
{

class Vector2
{
public:
  float x;
  float y;

  Vector2();
  Vector2(float x, float y);

  Vector2 operator-(Vector2 param);
  Vector2 operator+(Vector2 param);

};

}

}

#endif

