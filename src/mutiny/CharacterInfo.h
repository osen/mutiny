#ifndef MUTINY_ENGINE_CHARACTERINFO_H
#define MUTINY_ENGINE_CHARACTERINFO_H

#include "Rect.h"

namespace mutiny
{

namespace engine
{

struct CharacterInfo
{
public:
  char index;
  Rect uv;
  Rect vert;

  int getWidth() { return uv.width; }

};

}

}

#endif

