#ifndef MUTINY_ENGINE_RANDOM_H
#define MUTINY_ENGINE_RANDOM_H

namespace mutiny
{

namespace engine
{

class Random
{
public:
  static float getValue();
  static float range(float min, float max);

};

}

}

#endif

