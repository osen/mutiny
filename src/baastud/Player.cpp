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
  AnimatedMeshRenderer* mr = getGameObject()->addComponent<AnimatedMeshRenderer>();
  AnimatedMesh* mesh = Resources::load<AnimatedMesh>("models/sheep/sheep");
  mr->setAnimatedMesh(mesh);

  getGameObject()->addComponent<CharacterController>();
}

void Player::onUpdate()
{
  if(Input::getKey(KeyCode::RIGHT) == true)
  {
    getGameObject()->getTransform()->rotate(Vector3(0, 1, 0) * 100 * Time::getDeltaTime());
  }

  if(Input::getKey(KeyCode::UP) == true)
  {
    getGameObject()->getTransform()->translate(getGameObject()->getTransform()->getForward() * 10 * Time::getDeltaTime());
    //getGameObject()->getTransform()->translate(getGameObject()->getTransform()->getPosition() + Vector3(0, -1, 0));
  }

  CharacterController* cc = getGameObject()->getComponent<CharacterController>();

  cc->simpleMove(Vector3(0, -1, 0) * Time::getDeltaTime());
}
