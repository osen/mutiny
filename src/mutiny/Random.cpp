#include "Random.h"

#include <cstdlib>

namespace mutiny
{

namespace engine
{

float Random::getValue()
{
  return (float)rand() / (float)RAND_MAX;
}

float Random::range(float min, float max)
{
  return min + (getValue() * (max - min));
}

}

}

