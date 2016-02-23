#ifndef MUTINY_ENGINE_MESHRENDERER_H
#define MUTINY_ENGINE_MESHRENDERER_H

#include "Component.h"
#include "internal/gcmm.h"

#include <GL/glew.h>

#include <memory>
#include <vector>

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
  MeshRenderer();
  virtual ~MeshRenderer();

  void setMaterial(Material* material);
  void setMaterials(internal::gc::list<Material*>* materials);
  internal::gc::list<Material*>* getMaterials();
  Material* getMaterial();

private:
  virtual void render();

  internal::gc::list<Material*>* materials;

};

}

}

#endif

