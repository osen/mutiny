#include "Sheep.h"
#include "Fence.h"
#include "GameScreen.h"
#include "Audio.h"

#include <iostream>

using namespace mutiny::engine;

int Sheep::random(int min, int max)
{
  //srand(time(NULL));

  return rand() % ((max + 1) - min) + min;
}

GameObject* Sheep::create(GameScreen* gameScreen)
{
  GameObject* mainGo = new GameObject("Sheep");
  Sheep* sheep = mainGo->addComponent<Sheep>();
  sheep->gameScreen = gameScreen;

  return mainGo;
}

void Sheep::onStart()
{
  getGameObject()->setTag("sheep");
  state = 0;
  stateTimeout = rand() % 1000;
  sheepMr = getGameObject()->addComponent<AnimatedMeshRenderer>();
  AnimatedMesh* mesh = Resources::load<AnimatedMesh>("models/sheep/sheep");
  sheepMr->setAnimatedMesh(mesh);

  walkAnimation = Resources::load<Animation>("models/sheep/run.anm");
  eatAnimation = Resources::load<Animation>("models/sheep/eat.anm");

  sheepMr->setAnimation(eatAnimation);
  sheepMr->setFps(1);
  sheepMr->play();

  getGameObject()->addComponent<CharacterController>();

  getGameObject()->getTransform()->translate(Vector3(rand() % 20 + 1, 0, rand() % 20 + 1));

  getGameObject()->getTransform()->rotate(Vector3(0, rand() % 360, 0));
}

void Sheep::freeze()
{
  state = 2;
  sheepMr->setAnimation(NULL);
}

void Sheep::onUpdate()
{
  if(state == 2)
  {
    return;
  }

  if(state == 0)
  {
    getGameObject()->getTransform()->translate(getGameObject()->getTransform()->getForward() * 10.0f * Time::getDeltaTime());
    getGameObject()->getTransform()->rotate(Vector3(0, 1, 0));
  }

  CharacterController* cc = getGameObject()->getComponent<CharacterController>();

  cc->simpleMove(Vector3(0, -5, 0) * Time::getDeltaTime());
  stateTimeout -= Time::getDeltaTime() * 1000.0f;

  if(stateTimeout < 0)
  {
    stateTimeout = rand() % 3000;

    state = random(0, 10);
    //std::cout << state << std::endl;

    if(state == 0)
    {
      gameScreen->getAudio()->playSound(0);
      sheepMr->setAnimation(walkAnimation);
      sheepMr->setFps(4);
    }
    else
    {
      sheepMr->setAnimation(eatAnimation);
      sheepMr->setFps(1);
    }
  }

  Fence* fence = gameScreen->getFence()->getComponent<Fence>();
  Transform* transform = getGameObject()->getTransform();

  while(transform->getPosition().x > fence->getBounds().extents.x - 1)
  {
    cc->simpleMove(Vector3(-0.1f, 0, 0));
    transform->rotate(Vector3(0, 10, 0));
  }

  while(transform->getPosition().x < -fence->getBounds().extents.x + 1)
  {
    cc->simpleMove(Vector3(0.1f, 0, 0));
    transform->rotate(Vector3(0, 10, 0));
  }

  while(transform->getPosition().z > fence->getBounds().extents.z - 1)
  {
    cc->simpleMove(Vector3(0, 0, -0.1f));
    transform->rotate(Vector3(0, 10, 0));
  }

  while(transform->getPosition().z < -fence->getBounds().extents.z + 1)
  {
    cc->simpleMove(Vector3(0, 0, 0.1f));
    transform->rotate(Vector3(0, 10, 0));
  }
  
}


