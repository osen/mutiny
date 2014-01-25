#include "Player.h"
#include "GameScreen.h"
#include "Fence.h"
#include "Audio.h"
#include "Sheep.h"
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
  state = 0;
  mr = getGameObject()->addComponent<AnimatedMeshRenderer>();
  AnimatedMesh* mesh = Resources::load<AnimatedMesh>("models/sheep/sheep");
  mr->setAnimatedMesh(mesh);

  walkAnimation = Resources::load<Animation>("models/sheep/run.anm");
  idleAnimation = Resources::load<Animation>("models/sheep/idle.anm");
  sprintAnimation = Resources::load<Animation>("models/sheep/sprint.anm");
  humpAnimation = Resources::load<Animation>("models/sheep/hump.anm");

  mr->setAnimation(idleAnimation);
  mr->setFps(4);
  mr->play();

  getGameObject()->getTransform()->setPosition(Vector3(0, 10, 0));

  getGameObject()->addComponent<CharacterController>();
}

void Player::onUpdate()
{
  bool setToIdle = true;

  if(state == 0)
  {
    if(Input::getKey(KeyCode::RIGHT) == true)
    {
      mr->setAnimation(walkAnimation);
      getGameObject()->getTransform()->rotate(Vector3(0, 1, 0) * 100 * Time::getDeltaTime());
      setToIdle = false;
    }
    else if(Input::getKey(KeyCode::LEFT) == true)
    {
      mr->setAnimation(walkAnimation);
      getGameObject()->getTransform()->rotate(Vector3(0, -1, 0) * 100 * Time::getDeltaTime());
      setToIdle = false;
    }

    if(Input::getKey(KeyCode::UP) == true)
    {
      mr->setAnimation(walkAnimation);
      getGameObject()->getTransform()->translate(getGameObject()->getTransform()->getForward() * 8 * Time::getDeltaTime());
      setToIdle = false;
      //getGameObject()->getTransform()->translate(getGameObject()->getTransform()->getPosition() + Vector3(0, -1, 0));
    }

    if(setToIdle == true)
    {
      mr->setAnimation(idleAnimation);
    }

    if(Input::getKey(KeyCode::SPACE) == true)
    {
      gameScreen->getCamera()->toggleEventMode();
      gameScreen->getAudio()->playSound(1);
      mr->setAnimation(sprintAnimation);
      mr->setFps(4);
      state = 1;
    }
  }
  else if(state == 1)
  {
    if(Input::getKey(KeyCode::RIGHT) == true)
    {
      getGameObject()->getTransform()->rotate(Vector3(0, 1, 0) * 100 * Time::getDeltaTime());
    }
    else if(Input::getKey(KeyCode::LEFT) == true)
    {
      getGameObject()->getTransform()->rotate(Vector3(0, -1, 0) * 100 * Time::getDeltaTime());
    }

    getGameObject()->getTransform()->translate(getGameObject()->getTransform()->getForward() * 10 * Time::getDeltaTime());

    std::vector<GameObject*> sheepGos;
    GameObject::findGameObjectsWithTag("sheep", &sheepGos);

    for(int i = 0; i < sheepGos.size(); i++)
    {
      float dist = Vector3::getDistance(sheepGos.at(i)->getTransform()->getPosition(), getGameObject()->getTransform()->getPosition());
      std::cout << dist << std::endl;

      if(dist < 1)
      {
        sheepGos.at(i)->getTransform()->setParent(getGameObject()->getTransform());
        sheepGos.at(i)->getComponent<Sheep>()->freeze();
        state = 2;
        mr->setAnimation(humpAnimation);
        mr->setFps(4);
        break;
        //Object::destroy(sheepGos.at(i));
      }
    }
  }

  CharacterController* cc = getGameObject()->getComponent<CharacterController>();

  cc->simpleMove(Vector3(0, -5, 0) * Time::getDeltaTime());

  Fence* fence = gameScreen->getFence()->getComponent<Fence>();

  Transform* transform = getGameObject()->getTransform();

  while(transform->getPosition().x > fence->getBounds().extents.x - 1)
  {
    state = 0;
    cc->simpleMove(Vector3(-0.1f, 0, 0));
  }

  while(transform->getPosition().x < -fence->getBounds().extents.x + 1)
  {
    state = 0;
    cc->simpleMove(Vector3(0.1f, 0, 0));
  }

  while(transform->getPosition().z > fence->getBounds().extents.z - 1)
  {
    state = 0;
    cc->simpleMove(Vector3(0, 0, -0.1f));
  }

  while(transform->getPosition().z < -fence->getBounds().extents.z + 1)
  {
    state = 0;
    cc->simpleMove(Vector3(0, 0, 0.1f));
  }

  keepInBounds();
}

void Player::keepInBounds()
{

}
