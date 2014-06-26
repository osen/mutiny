#ifndef MUTINY_ENGINE_RECT_H
#define MUTINY_ENGINE_RECT_H

namespace mutiny
{

namespace engine
{

class Vector3;
class Vector2;
class Rect
{
public:
  float x;
  float y;
  float width;
  float height;

  Rect();
  Rect(float x, float y, float width, float height);

  bool contains(Vector3 point);
  bool contains(Vector2 point);

};

}

}

#endif

