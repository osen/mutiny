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

  void setMaterial(arc<Material> material);
  void setMaterials(std::vector<arc<Material> > materials);
  void getMaterials(std::vector<arc<Material> >& materials);
  arc<Material> getMaterial();

private:
  virtual void render();

  std::vector<arc<Material> > materials;

};

}

}

#endif

