#ifndef MUTINY_ENGINE_ANIMATEDMESH_H
#define MUTINY_ENGINE_ANIMATEDMESH_H

#include "../Mesh.h"
#include "../Object.h"
#include "../Bounds.h"

#include <GL/glew.h>

#include <vector>
#include <string>
#include <memory>

namespace mutiny
{

namespace engine
{

class Resources;

class AnimatedMesh : public Object
{
  friend class mutiny::engine::Resources;

public:
  void recalculateBounds();
  Mesh* getMesh(int index);
  Bounds getBounds();
  int getMeshCount();

private:
  static AnimatedMesh* load(std::string path);

  AnimatedMesh();

  std::vector<std::shared_ptr<Mesh> > meshes;
  Bounds bounds;

};

}

}

#endif

