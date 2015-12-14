#include "WaterScreen.h"
#include "WaterCamera.h"

using namespace mutiny::engine;

GameObject* WaterScreen::create()
{
  GameObject* mainGo = new GameObject("WaterScreen");
  mainGo->addComponent<WaterScreen>();

  return mainGo;
}

void WaterScreen::onAwake()
{
  accel = 0.0f;
  WaterCamera::create();
  effectUp = true;
  effectOffset = 0.0f;
  texOffset = 0.0f;

  waterGo = new GameObject("Water");
  waterGo->getTransform()->rotate(Vector3(0, 180, 0));
  waterGo->getTransform()->translate(Vector3(0, -1, 0));
  waterMr = waterGo->addComponent<MeshRenderer>();
  MeshFilter* waterMf = waterGo->addComponent<MeshFilter>();
  waterMf->setMesh(Resources::load<Mesh>("models/water/water"));
  waterMaterial = Resources::load<Material>("shaders/water");
  waterMr->setMaterial(waterMaterial);
  arc<Texture2d> waterTexture = Resources::load<Texture2d>("models/water/water");
  waterMaterial->setMainTexture(waterTexture.cast<Texture>());

  playerGo = new GameObject("Player");
  playerGo->getTransform()->setPosition(Vector3(0, 0, 0));

  playerMr = playerGo->addComponent<AnimatedMeshRenderer>();

  arc<AnimatedMesh> mesh = Resources::load<AnimatedMesh>("models/captain/captain");
  playerMr->setAnimatedMesh(mesh);

  for(int i = 0; i < playerMr->getRoot()->getTransform()->getChildCount(); i++)
  {
    if(playerMr->getRoot()->getTransform()->getChild(i)->getGameObject()->getName() == "Lightsaber")
    {
      arc<Material> fullRed = Resources::load<Material>("shaders/accum/full_red");
      fullRed->setMainTexture(Resources::load<Texture2d>("models/captain/captain").cast<Texture>());
      playerMr->getRoot()->getTransform()->getChild(i)->getGameObject()->getComponent<MeshRenderer>()
        ->setMaterial(fullRed);
    }
  }

  runAnimation = Resources::load<Animation>("models/captain/run.anm");
  idleAnimation = Resources::load<Animation>("models/captain/idle.anm");
  jumpAnimation = Resources::load<Animation>("models/captain/jump.anm");
  playerMr->setAnimation(idleAnimation);
  playerMr->setFps(1);
  playerMr->play();

  //Mesh* mesh = Resources::load<Mesh>("models/captain/captain");
  //MeshFilter* playerMf = playerGo->addComponent<MeshFilter>();
  //playerMf->setMesh(mesh);
}

void WaterScreen::onUpdate()
{
  texOffset += Time::getDeltaTime() * 0.1f;

  if(texOffset >= 1.0f)
  {
    texOffset = 0.0f;
  }

  if(effectUp == true)
  {
    effectOffset += Time::getDeltaTime();

    if(effectOffset >= 1.0f)
    {
      effectOffset = 1.0f;
      effectUp = false;
    }
  }
  else
  {
    effectOffset -= Time::getDeltaTime();

    if(effectOffset <= 0.0f)
    {
      effectOffset = 0.0f;
      effectUp = true;
    }
  }

  waterMaterial->setFloat("in_Offset", effectOffset);
  waterMaterial->setFloat("in_TexOffset", texOffset);

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

void WaterScreen::onGui()
{
  if(Gui::button(Rect(Screen::getWidth() - 210, 10, 200, 50), "Back") == true)
  {
    Application::loadLevel("introduction");
  }
}

