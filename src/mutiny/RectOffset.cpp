#include "RectOffset.h"

namespace mutiny
{

namespace engine
{

RectOffset::RectOffset()
{
  left = 0;
  right = 0;
  top = 0;
  bottom = 0;
}

RectOffset::RectOffset(float left, float right, float top, float bottom)
{
  this->left = left;
  this->right = right;
  this->top = top;
  this->bottom = bottom;
}

}

}

