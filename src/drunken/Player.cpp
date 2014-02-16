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
  AnimatedMesh* mesh = Resources::load<AnimatedMesh>("models/cowboy/cowboy");
  mr->setAnimatedMesh(mesh);

  walkAnimation = Resources::load<Animation>("models/cowboy/run.anm");
  idleAnimation = Resources::load<Animation>("models/cowboy/idle.anm");
  shootAnimation = Resources::load<Animation>("models/cowboy/sprint.anm");
  duckAnimation = Resources::load<Animation>("models/cowboy/hump.anm");

  mr->setAnimation(idleAnimation);
  mr->setFps(4);
  mr->play();

  getGameObject()->getTransform()->setPosition(Vector3(0, 1, 0));
  getGameObject()->getTransform()->setRotation(Vector3(0, 90, 0));
  getGameObject()->addComponent<CharacterController>();

  addPeacemaker();
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

void Player::addPeacemaker()
{
  Mesh* mesh = Resources::load<Mesh>("models/peacemaker/peacemaker");
  Texture2d* tex = Resources::load<Texture2d>("models/peacemaker/peacemaker");

  GameObject* tGo = new GameObject();
  //tGo->getTransform()->setParent(getGameObject()->getTransform());
  MeshRenderer* mr = tGo->addComponent<MeshRenderer>();
  MeshFilter* mf = tGo->addComponent<MeshFilter>();

  Material* material = new Material(Resources::load<Material>("shaders/textured"));
  material->setMainTexture(tex);

  mr->setMaterial(material);
  mf->setMesh(mesh);
}

