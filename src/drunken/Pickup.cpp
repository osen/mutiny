#include "Pickup.h"
#include "GameScreen.h"
#include "Player.h"

#include <iostream>

using namespace mutiny::engine;

GameObject* Pickup::create(GameScreen* gameScreen, int type)
{
  GameObject* mainGo = new GameObject("Pickup");
  Pickup* pickup = mainGo->addComponent<Pickup>();
  pickup->type = type;
  pickup->gameScreen = gameScreen;

  return mainGo;
}

void Pickup::onStart()
{
  Mesh* mesh = NULL;
  Texture2d* tex = NULL;

  if(type == PICKUP_GUN)
  {
    mesh = Resources::load<Mesh>("models/peacemaker/peacemaker");
    tex = Resources::load<Texture2d>("models/peacemaker/peacemaker");
    getGameObject()->getTransform()->setPosition(Vector3(10, 0, 0));
  }

  MeshRenderer* mr = getGameObject()->addComponent<MeshRenderer>();
  MeshFilter* mf = getGameObject()->addComponent<MeshFilter>();

  Material* material = new Material(Resources::load<Material>("shaders/textured"));
  material->setMainTexture(tex);

  mr->setMaterial(material);
  mf->setMesh(mesh);

  getGameObject()->getTransform()->setRotation(Vector3(-90, 90, 0));
}

void Pickup::onUpdate()
{
  Player* player = gameScreen->getPlayer();

  if(Vector3::getDistance(player->getGameObject()->getTransform()->getPosition(), getGameObject()->getTransform()->getPosition()) < 1)
  {
    if(type == PICKUP_GUN)
    {
      player->addPeacemaker();
    }

    Object::destroy(getGameObject());
  }

  getGameObject()->getTransform()->rotate(Vector3(0, 180, 0) * Time::getDeltaTime());
}
