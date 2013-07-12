#ifndef MUTINY_ENGINE_PARTICLEEMITTER_H
#define MUTINY_ENGINE_PARTICLEEMITTER_H

#include "Behaviour.h"
#include "Particle.h"

#include <vector>

namespace mutiny
{

namespace engine
{

class ParticleRenderer;

class ParticleEmitter : public Behaviour
{
  friend class mutiny::engine::ParticleRenderer;

public:
  virtual ~ParticleEmitter();

private:
  std::vector<Particle> particles;

  virtual void onStart();
  virtual void onUpdate();

};

}

}

#endif

