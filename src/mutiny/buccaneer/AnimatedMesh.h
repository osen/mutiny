#ifndef MUTINY_ENGINE_ANIMATEDMESH_H
#define MUTINY_ENGINE_ANIMATEDMESH_H

#include "../Mesh.h"
#include "../Object.h"
#include "../Bounds.h"
#include "../Vector3.h"
#include "../ref.h"

#include <GL/glew.h>

#include <vector>
#include <string>
#include <memory>

namespace mutiny
{

namespace engine
{

class Resources;
class Texture2d;

class AnimatedMesh : public Object
{
  friend class mutiny::engine::Resources;

public:
  AnimatedMesh();
  ~AnimatedMesh();
  void recalculateBounds();
  ref<Mesh> getMesh(int index);
  Bounds getBounds();
  int getMeshCount();
  ref<Texture2d> getTexture(int mesh, int submesh);
  std::string getMeshName(int mesh);
  Vector3 getMeshOffset(int mesh);

private:
  static ref<AnimatedMesh> load(std::string path);

  std::vector<std::vector<ref<Texture2d> > > textures;
  std::vector<shared<Mesh> > meshes;
  std::vector<std::string> meshNames;
  std::vector<Vector3> meshOffsets;
  Bounds bounds;

};

}

}

#endif

