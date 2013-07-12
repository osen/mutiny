#ifndef MUTINY_ENGINE_MESHRENDERER_H
#define MUTINY_ENGINE_MESHRENDERER_H

#include "Component.h"

#include <GL/glew.h>

#include <memory>

namespace mutiny
{

namespace engine
{

class Mesh;
class GameObject;
class Material;

class MeshRenderer : public Component
{
  friend class mutiny::engine::GameObject;

public:
  virtual ~MeshRenderer();

  void setMaterial(Material* material);
  Material* getMaterial();

private:
  Material* material;

  virtual void render();
  virtual void awake();

};

}

}

#endif

