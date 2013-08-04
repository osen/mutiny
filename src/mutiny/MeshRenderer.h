#ifndef MUTINY_ENGINE_MESHRENDERER_H
#define MUTINY_ENGINE_MESHRENDERER_H

#include "Component.h"

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
  virtual ~MeshRenderer();

  void setMaterial(Material* material);
  void setMaterials(std::vector<Material*> materials);
  Material* getMaterial();

private:
  std::vector<Material*> materials;

  virtual void render();
  virtual void awake();

};

}

}

#endif

