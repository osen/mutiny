#ifndef MUTINY_ENGINE_CHARACTERCONTROLLER_H
#define MUTINY_ENGINE_CHARACTERCONTROLLER_H

#include "Collider.h"
#include "Bounds.h"
#include "Collision.h"

namespace mutiny
{

namespace engine
{

class MeshCollider;
class Mesh;
class GameObject;

class CharacterController : public Collider
{
  friend class mutiny::engine::GameObject;

public:
  virtual ~CharacterController();

  void simpleMove(Vector3 speed);
  bool isGrounded();

private:
  bool grounded;

  virtual void awake();
  virtual void update();

  void checkCollision(ref<MeshCollider> collider);
  Vector3 crossProduct(Vector3& a, Vector3& b);
  Vector3 findNormal(Vector3 a, Vector3 b, Vector3 c);
  bool colliding(Vector3 center, Vector3 half, Vector3 a, Vector3 b, Vector3 c);
  Vector3 handleCollision(Collision collision, Vector3 pos, Vector3 bounds);
  Vector3 handleStep(Collision collision, Vector3 pos, Vector3 bounds);

};

}

}

#endif

