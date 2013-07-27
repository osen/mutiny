#ifndef MUTINY_ENGINE_RECT_H
#define MUTINY_ENGINE_RECT_H

namespace mutiny
{

namespace engine
{

class Vector3;
class Rect
{
public:
  int x;
  int y;
  int width;
  int height;

  Rect(int x, int y, int width, int height);

  bool contains(Vector3 point);

};

}

}

#endif

