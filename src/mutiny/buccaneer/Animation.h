#ifndef MUTINY_ENGINE_ANIMATION_H
#define MUTINY_ENGINE_ANIMATION_H

#include "../Object.h"

#include <string>

namespace mutiny
{

namespace engine
{

class Resources;

class Animation : public Object
{
  friend class mutiny::engine::Resources;

private:
  static Animation* load(std::string path);

};

}

}

#endif

