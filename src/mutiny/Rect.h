#ifndef MUTINY_ENGINE_RECT_H
#define MUTINY_ENGINE_RECT_H

#include "Vector2.h"

namespace mutiny
{

namespace engine
{

class Vector3;
class Rect
{
public:
  float x;
  float y;
  float width;
  float height;

  Rect();
  Rect(float x, float y, float width, float height);
  Rect(Vector2 position, Vector2 size);

  bool contains(Vector3 point);
  bool contains(Vector2 point);

};

}

}

#endif

