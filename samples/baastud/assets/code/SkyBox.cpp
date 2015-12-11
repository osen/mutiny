#include "SkyBox.h"

#include <vector>

using namespace mutiny::engine;

SkyBox* SkyBox::create(arc<GameObject> playerGo)
{
  GameObject* skyboxGo = new GameObject("SkyBox");
  SkyBox* skybox = skyboxGo->addComponent<SkyBox>();
  skybox->playerGo = playerGo;

  return skybox;
}

void SkyBox::onAwake()
{
  Debug::log("SkyBox awoken");

  // Front
  std::vector<Vector3> vertices;
  vertices.push_back(Vector3(-200, -100, 150));
  vertices.push_back(Vector3(-200, 100, 150));
  vertices.push_back(Vector3(200, 100, 150));
  vertices.push_back(Vector3(200, 100, 150));
  vertices.push_back(Vector3(200, -100, 150));
  vertices.push_back(Vector3(-200, -100, 150));

  std::vector<Vector2> uv;
  uv.push_back(Vector2(0, 1));
  uv.push_back(Vector2(0, 0));
  uv.push_back(Vector2(2, 0));
  uv.push_back(Vector2(2, 0));
  uv.push_back(Vector2(2, 1));
  uv.push_back(Vector2(0, 1));

  // Right
  vertices.push_back(Vector3(200, -100, 200));
  vertices.push_back(Vector3(200, 100, 200));
  vertices.push_back(Vector3(200, 100, -200));
  vertices.push_back(Vector3(200, 100, -200));
  vertices.push_back(Vector3(200, -100, -200));
  vertices.push_back(Vector3(200, -100, 200));

  uv.push_back(Vector2(0, 1));
  uv.push_back(Vector2(0, 0));
  uv.push_back(Vector2(2, 0));
  uv.push_back(Vector2(2, 0));
  uv.push_back(Vector2(2, 1));
  uv.push_back(Vector2(0, 1));

  // Back
  vertices.push_back(Vector3(200, -100, -200));
  vertices.push_back(Vector3(200, 100, -200));
  vertices.push_back(Vector3(-200, 100, -200));
  vertices.push_back(Vector3(-200, 100, -200));
  vertices.push_back(Vector3(-200, -100, -200));
  vertices.push_back(Vector3(200, -100, -200));

  uv.push_back(Vector2(0, 1));
  uv.push_back(Vector2(0, 0));
  uv.push_back(Vector2(2, 0));
  uv.push_back(Vector2(2, 0));
  uv.push_back(Vector2(2, 1));
  uv.push_back(Vector2(0, 1));

  // Left
  vertices.push_back(Vector3(-200, -100, -200));
  vertices.push_back(Vector3(-200, 100, -200));
  vertices.push_back(Vector3(-200, 100, 200));
  vertices.push_back(Vector3(-200, 100, 200));
  vertices.push_back(Vector3(-200, -100, 200));
  vertices.push_back(Vector3(-200, -100, -200));

  uv.push_back(Vector2(0, 1));
  uv.push_back(Vector2(0, 0));
  uv.push_back(Vector2(2, 0));
  uv.push_back(Vector2(2, 0));
  uv.push_back(Vector2(2, 1));
  uv.push_back(Vector2(0, 1));

  std::vector<int> triangles;
  triangles.push_back(0);
  triangles.push_back(1);
  triangles.push_back(2);
  triangles.push_back(3);
  triangles.push_back(4);
  triangles.push_back(5);
  triangles.push_back(6);
  triangles.push_back(7);
  triangles.push_back(8);
  triangles.push_back(9);
  triangles.push_back(10);
  triangles.push_back(11);
  triangles.push_back(12);
  triangles.push_back(13);
  triangles.push_back(14);
  triangles.push_back(15);
  triangles.push_back(16);
  triangles.push_back(17);
  triangles.push_back(18);
  triangles.push_back(19);
  triangles.push_back(20);
  triangles.push_back(21);
  triangles.push_back(22);
  triangles.push_back(23);

  Mesh* mesh = new Mesh();
  mesh->setVertices(vertices);
  mesh->setUv(uv);
  mesh->setTriangles(triangles, 0);

  MeshFilter* meshFilter = getGameObject()->addComponent<MeshFilter>();
  meshFilter->setMesh(mesh);

  Texture2d* texture = Resources::load<Texture2d>("textures/clouds");

  //Texture2d* texture = new Texture2d(1, 1);
  //texture->setPixel(0, 0, Color(1, 0, 0));
  //texture->apply();

  Material* material = new Material(Resources::load<Material>("shaders/Internal-MeshRendererTexture"));
  material->setMainTexture(texture);

  MeshRenderer* meshRenderer = getGameObject()->addComponent<MeshRenderer>();
  meshRenderer->setMaterial(material);

  //getGameObject()->getTransform()->translate(Vector3(0, 0, 10));
  //getGameObject()->getTransform()->rotate(Vector3(0, 180, 0));
}

void SkyBox::onUpdate()
{
  //getGameObject()->getTransform()->rotate(Vector3(0, 100, 0) * Time::getDeltaTime());
  //getGameObject()->getTransform()->translate(Vector3(0, Time::getDeltaTime(), 0));
  Vector3 pos = getGameObject()->getTransform()->getPosition();
  //pos.x = playerGo->getTransform()->getPosition().x;
  getGameObject()->getTransform()->setPosition(pos);
}
