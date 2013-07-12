#ifndef MUTINY_ENGINE_PARTICLE_H
#define MUTINY_ENGINE_PARTICLE_H

#include "Vector3.h"
#include "Color.h"

namespace mutiny
{

namespace engine
{

class Particle
{
public:
  Vector3 position;
  Vector3 velocity;
  float energy;
  float startEnergy;
  float size;
  float rotation;
  float angularVelocity;
  Color color;

};

}

}

#endif

