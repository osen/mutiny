#include "Level.h"

using namespace mutiny::engine;

Level* Level::create(GameObject* playerGo)
{
  GameObject* gameObject = new GameObject("Level");
  Level* level = gameObject->addComponent<Level>();
  level->playerGo = playerGo;
  return level;
}

void Level::onAwake()
{
  Material* material = NULL;

  resetCooldown = 8.5;

  Texture* texture = Resources::load<Texture2d>("models/level/level");
  Mesh* mesh = Resources::load<Mesh>("models/level/level");
  getGameObject()->addComponent<MeshFilter>()->setMesh(mesh);
  material = Resources::load<Material>("shaders/textured");
  getGameObject()->addComponent<MeshRenderer>()->setMaterial(material);
  material->setMainTexture(texture);

  MeshCollider* meshCollider = getGameObject()->addComponent<MeshCollider>();

  //getGameObject()->getTransform()->translate(Vector3(0, -1.5f, 0));
}

void Level::onUpdate()
{
  resetCooldown -= Time::getDeltaTime();

  if(resetCooldown <= 0)
  {
    Vector3 pos = getGameObject()->getTransform()->getPosition();
    getGameObject()->getTransform()->setPosition(Vector3(playerGo->getTransform()->getPosition().x, pos.y, pos.z));
    resetCooldown = 8.5;
  }
}

