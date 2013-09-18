#ifndef MUTINY_ENGINE_ANIMATEDMESH_H
#define MUTINY_ENGINE_ANIMATEDMESH_H

#include "../Mesh.h"
#include "../Object.h"
#include "../Bounds.h"
#include "../Vector3.h"

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
  void recalculateBounds();
  Mesh* getMesh(int index);
  Bounds getBounds();
  int getMeshCount();
  Texture2d* getTexture(int mesh, int submesh);
  std::string getMeshName(int mesh);
  Vector3 getMeshOffset(int mesh);

private:
  static AnimatedMesh* load(std::string path);

  AnimatedMesh();

  std::vector<std::vector<Texture2d*> > textures;
  std::vector<std::shared_ptr<Mesh> > meshes;
  std::vector<std::string> meshNames;
  std::vector<Vector3> meshOffsets;
  Bounds bounds;

};

}

}

#endif

