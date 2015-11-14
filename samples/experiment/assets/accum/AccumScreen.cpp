#include "AccumScreen.h"
#include "AccumCamera.h"

using namespace mutiny::engine;

GameObject* AccumScreen::create()
{
  GameObject* mainGo = new GameObject("AccumScreen");
  mainGo->addComponent<AccumScreen>();

  return mainGo;
}

void AccumScreen::onAwake()
{
  accel = 0.0f;
  AccumCamera::create();
  playerGo = new GameObject("Player");
  playerGo->getTransform()->setPosition(Vector3(0, 0, 0));

  playerMr = playerGo->addComponent<AnimatedMeshRenderer>();

  AnimatedMesh* mesh = Resources::load<AnimatedMesh>("models/darth/darth");
  playerMr->setAnimatedMesh(mesh);

  for(int i = 0; i < playerMr->getRoot()->getTransform()->getChildCount(); i++)
  {
    if(playerMr->getRoot()->getTransform()->getChild(i)->getGameObject()->getName() == "Lightsaber")
    {
      Material* fullRed = Resources::load<Material>("shaders/accum/full_red");
      fullRed->setMainTexture(Resources::load<Texture2d>("models/darth/darth"));
      playerMr->getRoot()->getTransform()->getChild(i)->getGameObject()->getComponent<MeshRenderer>()
        ->setMaterial(fullRed);
    }
  }

  runAnimation = Resources::load<Animation>("models/darth/run.anm");
  idleAnimation = Resources::load<Animation>("models/darth/idle.anm");
  jumpAnimation = Resources::load<Animation>("models/darth/jump.anm");
  playerMr->setAnimation(idleAnimation);
  playerMr->setFps(1);
  playerMr->play();

  //Mesh* mesh = Resources::load<Mesh>("models/darth/darth");
  //MeshFilter* playerMf = playerGo->addComponent<MeshFilter>();
  //playerMf->setMesh(mesh);
}

void AccumScreen::onUpdate()
{
  //playerGo->getComponent<Transform>()->rotate(Vector3(0, -100, 0) * Time::getDeltaTime());
  bool setToIdle = true;

  if(playerGo->getTransform()->getPosition().y <= 0)
  {
    if(Input::getKey(KeyCode::RIGHT) == true)
    {
      playerMr->setAnimation(runAnimation);
      playerMr->setFps(10);
      playerGo->getTransform()->translate(Vector3(-10, 0, 0) * Time::getDeltaTime());
      playerGo->getTransform()->setRotation(Vector3(0, -90, 0));

      setToIdle = false;
    }
    else if(Input::getKey(KeyCode::LEFT) == true)
    {
      playerMr->setAnimation(runAnimation);
      playerMr->setFps(10);
      playerGo->getTransform()->translate(Vector3(10, 0, 0) * Time::getDeltaTime());
      playerGo->getTransform()->setRotation(Vector3(0, 90, 0));

      setToIdle = false;
    }
    else if(Input::getKey(KeyCode::DOWN) == true)
    {
      playerMr->setAnimation(runAnimation);
      playerMr->setFps(10);
      playerGo->getTransform()->setRotation(Vector3(0, 0, 0));

      setToIdle = false;
    }

    if(Input::getKey(KeyCode::UP) == true)
    {
      //accel = 2.0f;
      //accel = 1.0f;
      accel = 0.9f;
      playerGo->getTransform()->translate(Vector3(0, accel, 0));
      playerMr->setAnimation(jumpAnimation);
      playerMr->setFps(5);

      setToIdle = false;
    }

    if(setToIdle == true)
    {
      playerMr->setAnimation(idleAnimation);
      playerMr->setFps(1);
    }
  }
  else
  {
    accel -= 2.0f * Time::getDeltaTime();

    if(accel < -1.0)
    {
      accel = -1;
    }

    playerGo->getTransform()->translate(Vector3(0, accel * 20.0f * Time::getDeltaTime(), 0));

    if(Input::getKey(KeyCode::RIGHT) == true)
    {
      playerGo->getTransform()->translate(Vector3(-10, 0, 0) * Time::getDeltaTime());
      playerGo->getTransform()->setRotation(Vector3(0, -90, 0));
    }
    else if(Input::getKey(KeyCode::LEFT) == true)
    {
      playerGo->getTransform()->translate(Vector3(10, 0, 0) * Time::getDeltaTime());
      playerGo->getTransform()->setRotation(Vector3(0, 90, 0));
    }
  }
}

void AccumScreen::onGui()
{
  if(Gui::button(Rect(Screen::getWidth() - 210, 10, 200, 50), "Back") == true)
  {
    Application::loadLevel("introduction");
  }
}

