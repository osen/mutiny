#ifndef MUTINY_ENGINE_MESHRENDERER_H
#define MUTINY_ENGINE_MESHRENDERER_H

#include "Component.h"
#include "ref.h"

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

  void setMaterial(ref<Material> material);
  void setMaterials(std::vector<ref<Material> > materials);
  std::vector<ref<Material> > getMaterials();
  ref<Material> getMaterial();

private:
  virtual void render();

  std::vector<ref<Material> > materials;

};

}

}

#endif

