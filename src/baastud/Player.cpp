#include "Player.h"

#include <iostream>

using namespace mutiny::engine;

GameObject* Player::create()
{
  GameObject* mainGo = new GameObject("Player");
  mainGo->addComponent<Player>();

  return mainGo;
}

void Player::onAwake()
{
  MeshRenderer* mr = getGameObject()->addComponent<MeshRenderer>();
  MeshFilter* mf = getGameObject()->addComponent<MeshFilter>();
  Mesh* mesh = Resources::load<Mesh>("models/terrain/terrain");
  Texture2d* tex = Resources::load<Texture2d>("models/terrain/terrain");

  Material* material = new Material(Resources::load<Material>("shaders/textured"));
  material->setMainTexture(tex);

  mr->setMaterial(material);
  mf->setMesh(mesh);
  //AnimatedMeshRenderer* mr = getGameObject()->addComponent<AnimatedMeshRenderer>();
  //AnimatedMesh* mesh = Resources::load<AnimatedMesh>("models/sheep/sheep");
  //AnimatedMesh* mesh = Resources::load<AnimatedMesh>("models/terrain/terrain");
  //mr->setAnimatedMesh(mesh);
}

void Player::onUpdate()
{
  if(Input::getKey(KeyCode::RIGHT) == true)
  {
    getGameObject()->getTransform()->rotate(Vector3(0, 1, 0) * 100 * Time::getDeltaTime());
  }

  if(Input::getKey(KeyCode::UP) == true)
  {
    //getGameObject()->getTransform()->translate(getGameObject()->getTransform()->getForward() * 10 * Time::getDeltaTime());
    getGameObject()->getTransform()->translate(getGameObject()->getTransform()->getPosition() + Vector3(0, -1, 0));
  }
}
