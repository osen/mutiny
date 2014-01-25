#include "Player.h"
#include "GameScreen.h"
#include "Fence.h"

#include <iostream>

using namespace mutiny::engine;

GameObject* Player::create(GameScreen* gameScreen)
{
  GameObject* mainGo = new GameObject("Player");
  Player* player = mainGo->addComponent<Player>();
  player->gameScreen = gameScreen;

  return mainGo;
}

void Player::onAwake()
{
  AnimatedMeshRenderer* mr = getGameObject()->addComponent<AnimatedMeshRenderer>();
  AnimatedMesh* mesh = Resources::load<AnimatedMesh>("models/sheep/sheep");
  mr->setAnimatedMesh(mesh);

  walkAnimation = Resources::load<Animation>("models/sheep/run.anm");

  mr->setAnimation(walkAnimation);
  mr->setFps(4);
  mr->play();

  getGameObject()->getTransform()->setPosition(Vector3(0, 10, 0));

  getGameObject()->addComponent<CharacterController>();
}

void Player::onUpdate()
{
  if(Input::getKey(KeyCode::RIGHT) == true)
  {
    getGameObject()->getTransform()->rotate(Vector3(0, 1, 0) * 100 * Time::getDeltaTime());
  }
  else if(Input::getKey(KeyCode::LEFT) == true)
  {
    getGameObject()->getTransform()->rotate(Vector3(0, -1, 0) * 100 * Time::getDeltaTime());
  }

  if(Input::getKey(KeyCode::UP) == true)
  {
    getGameObject()->getTransform()->translate(getGameObject()->getTransform()->getForward() * 10 * Time::getDeltaTime());
    //getGameObject()->getTransform()->translate(getGameObject()->getTransform()->getPosition() + Vector3(0, -1, 0));
  }

  CharacterController* cc = getGameObject()->getComponent<CharacterController>();

  cc->simpleMove(Vector3(0, -5, 0) * Time::getDeltaTime());

  Fence* fence = gameScreen->getFence()->getComponent<Fence>();
  fence->getBounds();

  Transform* transform = getGameObject()->getTransform();

  while(transform->getPosition().x > fence->getBounds().extents.x - 1)
  {
    cc->simpleMove(Vector3(-0.1f, 0, 0));
  }

  while(transform->getPosition().x < -fence->getBounds().extents.x + 1)
  {
    cc->simpleMove(Vector3(0.1f, 0, 0));
  }

  while(transform->getPosition().z > fence->getBounds().extents.z - 1)
  {
    cc->simpleMove(Vector3(0, 0, -0.1f));
  }

  while(transform->getPosition().z < -fence->getBounds().extents.z + 1)
  {
    cc->simpleMove(Vector3(0, 0, 0.1f));
  }

  keepInBounds();
}

void Player::keepInBounds()
{

}
