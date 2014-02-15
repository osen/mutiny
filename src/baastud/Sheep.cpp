#include "Sheep.h"
#include "Fence.h"
#include "GameScreen.h"
#include "Audio.h"

#include <iostream>

using namespace mutiny::engine;

int Sheep::random(int min, int max)
{
  return rand() % ((max + 1) - min) + min;
}

GameObject* Sheep::create(GameScreen* gameScreen)
{
  GameObject* mainGo = new GameObject("Sheep");
  Sheep* sheep = mainGo->addComponent<Sheep>();
  sheep->gameScreen = gameScreen;

  return mainGo;
}

bool Sheep::isWolf()
{
  return wolf;
}

void Sheep::onStart()
{
  AnimatedMesh* mesh;

  wolf = false;
  getGameObject()->setTag("sheep");
  state = 0;

  if(rand() % 1000 > 700)
  {
    std::cout << "I am a wolf" << std::endl;
    wolf = true;
  }

  stateTimeout = rand() % 1000;
  sheepMr = getGameObject()->addComponent<AnimatedMeshRenderer>();

  if(wolf == false)
    mesh = Resources::load<AnimatedMesh>("models/sheep/sheep");
  else
    mesh = Resources::load<AnimatedMesh>("models/sheep/wolf");

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
    return;

  if(state == 0)
  {
    getGameObject()->getTransform()->translate(getGameObject()->getTransform()->getForward() * 8.0f * Time::getDeltaTime());
    getGameObject()->getTransform()->rotate(Vector3(0, 1, 0));
  }

  CharacterController* cc = getGameObject()->getComponent<CharacterController>();

  cc->simpleMove(Vector3(0, -5, 0) * Time::getDeltaTime());
  stateTimeout -= Time::getDeltaTime() * 1000.0f;

  if(stateTimeout < 0)
  {
    stateTimeout = rand() % 3000;

    if(random(0, 10) < 2)
    {
      state = 0;

      int rval = rand() % 100;

      if(rval > 97)
      {
        if(wolf == true)
          gameScreen->getAudio()->playSound(12);
        else
          gameScreen->getAudio()->playSound(0);
      }
      else if(rval > 93)
      {
        if(wolf == true)
          gameScreen->getAudio()->playSound(13);
        else
          gameScreen->getAudio()->playSound(1);
      }
      else if(rval > 90)
      {
        if(wolf == true)
          gameScreen->getAudio()->playSound(14);
        else
          gameScreen->getAudio()->playSound(2);
      }
      else if(rval > 85)
      {
        if(wolf == true)
          gameScreen->getAudio()->playSound(15);
        else
          gameScreen->getAudio()->playSound(3);
      }
      else if(rval > 82)
      {
        if(wolf == true)
          gameScreen->getAudio()->playSound(13);
        else
          gameScreen->getAudio()->playSound(4);
      }
      else if(rval >= 80)
      {
        if(wolf == true)
          gameScreen->getAudio()->playSound(14);
        else
          gameScreen->getAudio()->playSound(5);
      }

      sheepMr->setAnimation(walkAnimation);
      sheepMr->setFps(4);
    }
    else
    {
      state = 1;
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


