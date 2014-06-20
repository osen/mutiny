#include "Floor.h"

Floor* Floor::create()
{
  Floor* rtn;
  GameObject* go;

  go = new GameObject("_EDITOR_Floor");
  rtn = go->addComponent<Floor>();

  return rtn;
}

void Floor::onAwake()
{
  mesh.reset(new Mesh());

  std::vector<Vector3> positions;
  std::vector<Vector2> uvs;
  std::vector<int> triangles;

  material.reset(new
    Material(Resources::load<Shader>("shaders/EditorGridTexture")));

  positions.push_back(Vector3(100, 0, 100));
  positions.push_back(Vector3(100, 0, -100));
  positions.push_back(Vector3(-100, 0, -100));

  positions.push_back(Vector3(-100, 0, -100));
  positions.push_back(Vector3(-100, 0, 100));
  positions.push_back(Vector3(100, 0, 100));

  uvs.push_back(Vector2(0, 0));
  uvs.push_back(Vector2(0, 1));
  uvs.push_back(Vector2(1, 1));
  uvs.push_back(Vector2(1, 1));
  uvs.push_back(Vector2(1, 0));
  uvs.push_back(Vector2(0, 0));

  triangles.push_back(0);
  triangles.push_back(1);
  triangles.push_back(2);
  triangles.push_back(3);
  triangles.push_back(4);
  triangles.push_back(5);

  mesh->setVertices(positions);
  mesh->setUv(uvs);
  mesh->setTriangles(triangles, 0);

  MeshRenderer* mr = getGameObject()->addComponent<MeshRenderer>();
  mr->setMaterial(material.get());

  MeshFilter* mf = getGameObject()->addComponent<MeshFilter>();
  mf->setMesh(mesh.get());
}

