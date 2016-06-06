#ifndef MUTINY_ENGINE_MESH_H
#define MUTINY_ENGINE_MESH_H

#include "Vector3.h"
#include "Vector2.h"
#include "Object.h"
#include "Bounds.h"
#include "Color.h"
#include "internal/CWrapper.h"
#include "internal/gcmm.h"
#include "internal/glmm.h"

#include <GL/glew.h>

#include <vector>
#include <string>
#include <memory>

namespace mutiny
{

namespace engine
{

class Resources;
class MeshRenderer;
class Graphics;

class Mesh : public Object
{
  friend class mutiny::engine::Resources;
  friend class mutiny::engine::MeshRenderer;
  friend class mutiny::engine::Graphics;

public:
  void recalculateNormals();
  void recalculateBounds();

  void setVertices(std::vector<Vector3> vertices);
  void setTriangles(std::vector<int> triangles, int submesh);
  void setUv(std::vector<Vector2> uv);
  void setNormals(std::vector<Vector3> normals);
  void setColors(std::vector<Color> colors);

  std::vector<Vector3>& getVertices();
  std::vector<int>& getTriangles(int submesh);
  std::vector<Vector2>& getUv();
  std::vector<Vector3>& getNormals();
  std::vector<Color>& getColors();

  Bounds getBounds();
  int getSubmeshCount();

private:
  static Mesh* load(std::string path);
  static void freeBuffer(GLuint bufferId);

  std::vector<Vector3> vertices;
  std::vector<std::vector<int> > triangles;
  std::vector<Vector2> uv;
  std::vector<Vector3> normals;
  std::vector<Color> colors;

  std::vector<shared<gl::Uint> > positionBufferIds;
  std::vector<shared<gl::Uint> > uvBufferIds;
  std::vector<shared<gl::Uint> > normalBufferIds;

  Bounds bounds;

};

}

}

#endif

