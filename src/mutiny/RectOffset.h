#ifndef MUTINY_ENGINE_RECTOFFSET_H
#define MUTINY_ENGINE_RECTOFFSET_H

namespace mutiny
{

namespace engine
{

class RectOffset
{
public:
  float left;
  float right;
  float top;
  float bottom;

  RectOffset();
  RectOffset(float left, float right, float top, float bottom);

};

}

}

#endif

