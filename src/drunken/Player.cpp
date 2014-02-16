#include "Player.h"
#include "GameScreen.h"
#include "GameCamera.h"

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
  mr = getGameObject()->addComponent<AnimatedMeshRenderer>();
  AnimatedMesh* mesh = Resources::load<AnimatedMesh>("models/sheep/sheep");
  mr->setAnimatedMesh(mesh);

  walkAnimation = Resources::load<Animation>("models/sheep/run.anm");
  idleAnimation = Resources::load<Animation>("models/sheep/idle.anm");
  shootAnimation = Resources::load<Animation>("models/sheep/sprint.anm");
  duckAnimation = Resources::load<Animation>("models/sheep/hump.anm");

  mr->setAnimation(idleAnimation);
  mr->setFps(4);
  mr->play();

  getGameObject()->getTransform()->setPosition(Vector3(0, 1, 0));
  getGameObject()->getTransform()->setRotation(Vector3(0, 90, 0));
  getGameObject()->addComponent<CharacterController>();
}

void Player::onUpdate()
{
  CharacterController* cc = getGameObject()->getComponent<CharacterController>();

  if(Input::getKey(KeyCode::RIGHT) == true)
  {
    getGameObject()->getTransform()->translate(
      getGameObject()->getTransform()->getForward() * 8 * Time::getDeltaTime());
  }

  cc->simpleMove(Vector3(0, -5, 0) * Time::getDeltaTime());
}

void Player::onGui()
{

} 
