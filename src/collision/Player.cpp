#include "Player.h"

#include <vector>

using namespace mutiny::engine;

Player* Player::create()
{
  //GameObject* playerGo = new GameObject("Player");
  GameObject* playerGo = GameObject::createPrimitive(PrimitiveType::CUBE);
  Player* player = playerGo->addComponent<Player>();

  return player;
}

void Player::onAwake()
{
  Debug::log("Player awoken");

  Texture2d* texture = Resources::load<Texture2d>("textures/box");
  //Mesh* mesh = Resources::load<Mesh>("models/mower/mower");
  //getGameObject()->addComponent<MeshFilter>()->setMesh(mesh);
  //Material* material = Resources::load<Material>("shaders/textured");
  material = Resources::load<Material>("shaders/mower");
  //material->setFloat("in_Replace", 1.0f);
  material->setMainTexture(texture);
  getGameObject()->getComponent<MeshRenderer>()->setMaterial(material);

  getGameObject()->getTransform()->setPosition(Vector3(0, 10, 0));
  getGameObject()->getTransform()->setRotation(Vector3(0, 90, 0));
  getGameObject()->addComponent<CharacterController>();

  getGameObject()->addComponent<ParticleEmitter>();
  //Material* particleMaterial = Resources::load<Material>("shaders/particle");
  Material* particleMaterial = Resources::load<Material>("shaders/textured");
  particleMaterial->setMainTexture(Resources::load<Texture2d>("particles/grass"));
  getGameObject()->addComponent<ParticleRenderer>()->setMaterial(particleMaterial);
}

void Player::onUpdate()
{
  Vector3 pos = getGameObject()->getTransform()->getPosition();
  static float up = 0.0f;

  CharacterController* cc = getGameObject()->getComponent<CharacterController>();

  Vector3 movement;

  if(cc->isGrounded() == true)
  {
    if(Input::getKey(KeyCode::UP) == true)
    {
      up = 10.0f;
    }
  }

  material->setFloat("in_Replace", up / 10.0f);

  movement.y = (-5 + up) * Time::getDeltaTime();

  up -= 10.0f * Time::getDeltaTime();

  if(up < 0)
  {
    up = 0;
  }

  if(Input::getKey(KeyCode::RIGHT) == true)
  {
    movement.x = 5 * Time::getDeltaTime();
  }

  if(Input::getKey(KeyCode::LEFT) == true)
  {
    movement.x = -5 * Time::getDeltaTime();
  }

  cc->simpleMove(movement);
}
