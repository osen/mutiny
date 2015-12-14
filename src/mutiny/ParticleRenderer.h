#ifndef MUTINY_ENGINE_PARTICLERENDERER_H
#define MUTINY_ENGINE_PARTICLERENDERER_H

#include "Component.h"
#include "arc.h"

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

  void setMaterial(Material* material);
  arc<Material> getMaterial();

private:
  GLuint positionBufferId; arc<GLuint> _positionBufferId;
  GLuint uvBufferId; arc<GLuint> _uvBufferId;

  arc<Material> material;

  virtual void render();
  virtual void awake();

};

}

}

#endif

