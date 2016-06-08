#ifndef MUTINY_ENGINE_PARTICLERENDERER_H
#define MUTINY_ENGINE_PARTICLERENDERER_H

#include "Component.h"

#include <GL/glew.h>

#include <memory>

namespace mutiny
{

namespace engine
{

class GameObject;
class Material;

class ParticleRenderer : public Component
{
  friend class mutiny::engine::GameObject;

public:
  virtual ~ParticleRenderer();

  void setMaterial(ref<Material> material);
  ref<Material> getMaterial();

private:
  GLuint positionBufferId; GLuint* _positionBufferId;
  GLuint uvBufferId; GLuint* _uvBufferId;

  ref<Material> material;

  virtual void render();
  virtual void awake();

};

}

}

#endif

