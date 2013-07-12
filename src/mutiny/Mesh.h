#ifndef MUTINY_ENGINE_MESH_H
#define MUTINY_ENGINE_MESH_H

#include "Vector3.h"
#include "Vector2.h"
#include "Object.h"
#include "Bounds.h"

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

class Mesh : public Object
{
  friend class mutiny::engine::Resources;
  friend class mutiny::engine::MeshRenderer;

public:
  Mesh();

  void recalculateNormals();
  void recalculateBounds();

  void setVertices(std::vector<Vector3> vertices);
  void setTriangles(std::vector<int> triangles);
  void setUv(std::vector<Vector2> uv);
  void setNormals(std::vector<Vector3> normals);

  std::vector<Vector3>* getVertices();
  std::vector<int>* getTriangles();
  std::vector<Vector2>* getUv();
  std::vector<Vector3>* getNormals();

  Bounds getBounds();

private:
  static Mesh* load(std::string path);

  std::vector<Vector3> vertices;
  std::vector<int> triangles;
  std::vector<Vector2> uv;
  std::vector<Vector3> normals;

  GLuint positionBufferId; std::shared_ptr<void> _positionBufferId;
  GLuint uvBufferId; std::shared_ptr<void> _uvBufferId;
  GLuint normalBufferId; std::shared_ptr<void> _normalBufferId;

  Bounds bounds;

};

}

}

#endif

