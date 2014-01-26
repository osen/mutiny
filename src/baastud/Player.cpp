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
  hTimeout = 0;
  state = 0;
  speed = 10.0f;
  mr = getGameObject()->addComponent<AnimatedMeshRenderer>();
  AnimatedMesh* mesh = Resources::load<AnimatedMesh>("models/sheep/sheep");
  mr->setAnimatedMesh(mesh);

  censoredTexture = Resources::load<Texture2d>("textures/censored");

  walkAnimation = Resources::load<Animation>("models/sheep/run.anm");
  idleAnimation = Resources::load<Animation>("models/sheep/idle.anm");
  sprintAnimation = Resources::load<Animation>("models/sheep/sprint.anm");
  humpAnimation = Resources::load<Animation>("models/sheep/hump.anm");

  mr->setAnimation(idleAnimation);
  mr->setFps(4);
  mr->play();

  getGameObject()->getTransform()->setPosition(Vector3(0, 0, 0));

  getGameObject()->addComponent<CharacterController>();
}

void Player::onUpdate()
{
  bool setToIdle = true;

  if(Application::getLoadedLevelName() == "introduction")
  {
    getGameObject()->getTransform()->setRotation(Vector3(0, 180, 0));
    getGameObject()->getTransform()->setPosition(Vector3(-13, 0, -19));
    return;
  }

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

    getGameObject()->getTransform()->translate(getGameObject()->getTransform()->getForward() * speed * Time::getDeltaTime());

    std::vector<GameObject*> sheepGos;
    GameObject::findGameObjectsWithTag("sheep", &sheepGos);

    for(int i = 0; i < sheepGos.size(); i++)
    {
      float dist = Vector3::getDistance(sheepGos.at(i)->getTransform()->getPosition(), getGameObject()->getTransform()->getPosition());
      //std::cout << dist << std::endl;

      if(dist < 1)
      {
        hTarget = sheepGos.at(i);
        sheepGos.at(i)->getTransform()->setParent(getGameObject()->getTransform());
        sheepGos.at(i)->getTransform()->setLocalRotation(Vector3(0, 0, 0));
        sheepGos.at(i)->getTransform()->setLocalPosition(Vector3(0, 0, 2));
        sheepGos.at(i)->getComponent<Sheep>()->freeze();

        if(sheepGos.at(i)->getComponent<Sheep>()->isWolf() == true)
        {
          std::cout << "Currently humping wolf" << std::endl;
        }

        state = 2;
        gameScreen->getCamera()->toggleEventMode();
        mr->setAnimation(humpAnimation);
        mr->setFps(4);
        hTimeout = 2000.0f;
        break;
      }
    }

    speed += 0.5f * Time::getDeltaTime();

    if(speed > 15)
    {
      speed = 15;
    }
  }
  else if(state == 2)
  {
    hTimeout -= Time::getDeltaTime() * 1000;

    if(hTimeout < 0)
    {
      if(hTarget->getComponent<Sheep>()->isWolf() == true)
      {
        Debug::logWarning("Wolf was humped. Ending match");
      }

      Object::destroy(hTarget);
      gameScreen->getCamera()->toggleEventMode();
      state = 1;
      mr->setAnimation(sprintAnimation);
      mr->setFps(4);
      Sheep::create(gameScreen);
    }
  }

  CharacterController* cc = getGameObject()->getComponent<CharacterController>();

  cc->simpleMove(Vector3(0, -5, 0) * Time::getDeltaTime());

  Fence* fence = gameScreen->getFence()->getComponent<Fence>();

  Transform* transform = getGameObject()->getTransform();

  while(transform->getPosition().x > fence->getBounds().extents.x - 1)
  {
    if(state == 1)
      transform->setRotation(Vector3(0, rand() % 350 + 190, 0));
    //state = 0;
    cc->simpleMove(Vector3(-0.1f, 0, 0));
  }

  while(transform->getPosition().x < -fence->getBounds().extents.x + 1)
  {
    if(state == 1)
      transform->setRotation(Vector3(0, rand() % 170 + 10, 0));
    //state = 0;
    cc->simpleMove(Vector3(0.1f, 0, 0));
  }

  while(transform->getPosition().z > fence->getBounds().extents.z - 1)
  {
    if(state == 1)
      transform->setRotation(Vector3(0, rand() % 260 + 100, 0));
    //state = 0;
    cc->simpleMove(Vector3(0, 0, -0.1f));
  }

  while(transform->getPosition().z < -fence->getBounds().extents.z + 1)
  {
    if(state == 1)
      transform->setRotation(Vector3(0, rand() % 260 + 100, 0) * -1);
    //state = 0;
    cc->simpleMove(Vector3(0, 0, 0.1f));
  }
}

void Player::onGui()
{
  if(state == 2)
  {
    float texWidth = censoredTexture->getWidth() * 0.8f;
    float texHeight = censoredTexture->getHeight() * 0.8f;
    Gui::drawTexture(Rect((Screen::getWidth() / 2) - (texWidth / 2),
                          (Screen::getHeight() / 2) - (texHeight / 2),
                          texWidth, texHeight), censoredTexture);
  }
}
