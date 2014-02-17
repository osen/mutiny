#include "Player.h"
#include "GameScreen.h"
#include "GameCamera.h"

#include <iostream>

using namespace mutiny::engine;

Player* Player::create(GameScreen* gameScreen)
{
  GameObject* mainGo = new GameObject("Player");
  Player* player = mainGo->addComponent<Player>();
  player->gameScreen = gameScreen;

  return player;
}

void Player::onAwake()
{
  mr = getGameObject()->addComponent<AnimatedMeshRenderer>();
  AnimatedMesh* mesh = Resources::load<AnimatedMesh>("models/cowboy/cowboy");
  mr->setAnimatedMesh(mesh);

  walkAnimation = Resources::load<Animation>("models/cowboy/walk.anm");
  idleAnimation = Resources::load<Animation>("models/cowboy/idle.anm");
  shootAnimation = Resources::load<Animation>("models/cowboy/shoot.anm");
  duckAnimation = Resources::load<Animation>("models/cowboy/duck.anm");

  mr->setAnimation(idleAnimation);
  mr->setFps(1.0f);
  mr->play();

  getGameObject()->getTransform()->setPosition(Vector3(0, 1, 0));
  getGameObject()->getTransform()->setRotation(Vector3(0, 90, 0));
  getGameObject()->addComponent<CharacterController>();

  peacemakerGo = NULL;

  setupLegs();

  lmr->setFps(4);
}

void Player::setupLegs()
{
  legsGo = new GameObject();
  legsGo->getTransform()->setParent(getGameObject()->getTransform());

  lmr = legsGo->addComponent<AnimatedMeshRenderer>();
  AnimatedMesh* mesh = Resources::load<AnimatedMesh>("models/cowboy/cowboy_lower");
  lmr->setAnimatedMesh(mesh);

  legsGo->getTransform()->setLocalPosition(Vector3(0, 0, 0));
  legsGo->getTransform()->setLocalRotation(Vector3(0, 0, 0));
}

void Player::onUpdate()
{
  bool shouldIdle = true;

  CharacterController* cc = getGameObject()->getComponent<CharacterController>();

  if(Input::getKey(KeyCode::RIGHT) == true)
  {
    lmr->setAnimation(walkAnimation);
    lmr->play();
    shouldIdle = false;
    getGameObject()->getTransform()->translate(
      getGameObject()->getTransform()->getForward() * 8 * Time::getDeltaTime());
  }
  else if(Input::getKey(KeyCode::DOWN) == true)
  {
    mr->setAnimation(duckAnimation);
    mr->setFps(1.0f);
    //mr->play();
    shouldIdle = false;
  }
  else if(Input::getKey(KeyCode::SPACE) == true)
  {
    mr->setFps(10.0f);
    mr->setAnimation(shootAnimation);
    //mr->play();
    shouldIdle = false;
  }

  if(shouldIdle == true)
  {
    lmr->setAnimation(NULL);
    mr->setAnimation(idleAnimation);
    mr->setFps(1.0f);
    //mr->play();
  }

  cc->simpleMove(Vector3(0, -5, 0) * Time::getDeltaTime());

  //peacemakerGo->getTransform()->setLocalRotation(Vector3(0, 180, 0));
  //peacemakerGo->getTransform()->setLocalPosition(Vector3(0, 1, 0));
}

void Player::onGui()
{

}

void Player::addPeacemaker()
{
  if(peacemakerGo != NULL)
  {
    return;
  }

  Mesh* mesh = Resources::load<Mesh>("models/peacemaker/peacemaker");
  Texture2d* tex = Resources::load<Texture2d>("models/peacemaker/peacemaker");

  GameObject* tGo = new GameObject();

  for(int i = 0; i < mr->getRoot()->getTransform()->getChildCount(); i++)
  {
    if(mr->getRoot()->getTransform()->getChild(i)->getGameObject()->getName() == "RightLowerArm")
    {
      tGo->getTransform()->setParent(mr->getRoot()->getTransform()->getChild(i));
      //tGo->getTransform()->setLocalRotation(Vector3(-90, 180, 0));
      //tGo->getTransform()->setLocalPosition(Vector3(0, -2, 0));
      //tGo->getTransform()->setRotation(Vector3(0, -90, 0));
      tGo->getTransform()->setLocalRotation(Vector3(0, 0, 0));
      tGo->getTransform()->setLocalPosition(Vector3(0.1f, -1.1f, 0));
    }
  }

  peacemakerGo = tGo;

  MeshRenderer* mr = tGo->addComponent<MeshRenderer>();
  MeshFilter* mf = tGo->addComponent<MeshFilter>();

  Material* material = new Material(Resources::load<Material>("shaders/textured"));
  material->setMainTexture(tex);

  mr->setMaterial(material);
  mf->setMesh(mesh);
}

