#include "ParticleEmitter.h"
#include "_Time.h"
#include "GameObject.h"
#include "Transform.h"
#include "Debug.h"

namespace mutiny
{

namespace engine
{

ParticleEmitter::~ParticleEmitter()
{

}

void ParticleEmitter::onStart()
{
  Debug::log("Particle emitter started");
  for(int i = 0; i < 10; i++)
  {
    Particle particle;
    particle.position = getGameObject()->getTransform()->getPosition();
    particle.rotation = 0;
    particle.velocity = Vector3(-5.0, 0.1f, 0);
    particle.startEnergy = ((float)i + 1.0f) * 0.1f;
    particle.energy = particle.startEnergy;
    particles.push_back(particle);
  }
}

void ParticleEmitter::onUpdate()
{
  for(int i = 0; i < particles.size(); i++)
  {
    particles.at(i).position = particles.at(i).position + (particles.at(i).velocity * Time::getDeltaTime());
    particles.at(i).energy -= Time::getDeltaTime();

    if(particles.at(i).energy <= 0)
    {
      particles.at(i).position = getGameObject()->getTransform()->getPosition();
      particles.at(i).energy = particles.at(i).startEnergy;
    }
  }
}

}

}

