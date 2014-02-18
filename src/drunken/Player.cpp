#include "Player.h"
#include "GameScreen.h"
#include "GameCamera.h"
#include "Bullet.h"

#include <iostream>

#define IDLE 0
#define WALK 1
#define SHOOT 2
#define CROUCH 3
#define CRAWL 4

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
  state = IDLE;
  invulnTimeout = 0;
  health = 3;
  shootTimeout = 0;
  mr = getGameObject()->addComponent<AnimatedMeshRenderer>();
  AnimatedMesh* mesh = Resources::load<AnimatedMesh>("models/cowboy/cowboy");
  mr->setAnimatedMesh(mesh);

  heartTexture = Resources::load<Texture2d>("images/heart");

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

  if(invulnTimeout > 0)
  {
    invulnTimeout -= Time::getDeltaTime();
  }

  shootTimeout -= Time::getDeltaTime();
  CharacterController* cc = getGameObject()->getComponent<CharacterController>();

  if(state == IDLE)
  {
    if(Input::getKey(KeyCode::SPACE) == true)
    {
      state = round(Random::range(1, 4));
    }
  }

  if(state == WALK || state == CRAWL)
  {
    lmr->setAnimation(walkAnimation);
    lmr->play();
    shouldIdle = false;
    getGameObject()->getTransform()->translate(
      getGameObject()->getTransform()->getForward() * 8 * Time::getDeltaTime());
  }
  if(state == CROUCH || state == CRAWL)
  {
    mr->setAnimation(duckAnimation);
    mr->setFps(1.0f);
    //mr->play();
    shouldIdle = false;
  }
  if(state == SHOOT)
  {
    mr->setFps(10.0f);
    mr->setAnimation(shootAnimation);
    //mr->play();
    shouldIdle = false;
    tryShoot();
  }

  if(shouldIdle == true)
  {
    lmr->setAnimation(NULL);
    mr->setAnimation(idleAnimation);
    mr->setFps(1.0f);
    //mr->play();
  }

  if(Input::getKey(KeyCode::SPACE) == false)
  {
    state = IDLE;
  }

  cc->simpleMove(Vector3(0, -5, 0) * Time::getDeltaTime());

  std::vector<GameObject*> axeGos;
  GameObject::findGameObjectsWithTag("axe", &axeGos);

  for(int i = 0; i < axeGos.size(); i++)
  {
    if(Vector3::getDistance(axeGos.at(i)->getTransform()->getPosition(),
                                getGameObject()->getTransform()->getPosition()) < 4 &&
    mr->getAnimation() != duckAnimation &&
    invulnTimeout <= 0)
    {
      invulnTimeout = 3;
      health--;
      Debug::log("ouch!");
    }
  }

  //peacemakerGo->getTransform()->setLocalRotation(Vector3(0, 180, 0));
  //peacemakerGo->getTransform()->setLocalPosition(Vector3(0, 1, 0));
}

void Player::tryShoot()
{
  if(shootTimeout > 0)
  {
    return;
  }

  if(peacemakerGo == NULL)
  {
    return;
  }

  Bullet::create(peacemakerGo);
  shootTimeout = 0.33333f;
}

void Player::onGui()
{
  for(int i = 0; i < health; i++)
  {
    Gui::drawTexture(Rect(10 + ((heartTexture->getWidth() + 5) * i), 10, heartTexture->getWidth(), heartTexture->getHeight()), heartTexture);
  }
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

