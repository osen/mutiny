#include "CharacterController.h"
#include "Application.h"
#include "GameObject.h"
#include "MeshCollider.h"
#include "Mesh.h"
#include "ContactPoint.h"
#include "Transform.h"
#include "Matrix4x4.h"
#include "Collision.h"
#include "Debug.h"

#include "internal/tribox.h"

#include <cmath>

namespace mutiny
{

namespace engine
{

CharacterController::~CharacterController()
{

}

bool CharacterController::isGrounded()
{
  return grounded;
}

void CharacterController::simpleMove(Vector3 speed)
{
  Vector3 pos = getGameObject()->getTransform()->getPosition();
  getGameObject()->getTransform()->setPosition(pos + speed);
}

void CharacterController::awake()
{
  grounded = false;

  Collider::awake();
}

void CharacterController::update()
{
  grounded = false;

  std::vector<Object*> collidableObjects = GameObject::findObjectsOfType<MeshCollider>();

  for(int i = 0; i < collidableObjects.size(); i++)
  {
    MeshCollider* meshCollider = ((MeshCollider*)collidableObjects.at(i));

    if(meshCollider->getBounds().intersects(bounds) == true)
    {
      checkCollision(meshCollider);
    }
  }

  Collider::update();
}

void CharacterController::checkCollision(MeshCollider* collider)
{
  Vector3 pos = getGameObject()->getTransform()->getPosition();

  arc<Mesh> mesh = collider->getMesh();
  std::vector<Vector3>& vertices = mesh->getVertices();

  // We basically want to set the mesh to the origin, including its rotation.
  // If we rotate the mesh, then we need to make sure we rotate the characters bounds too
  // so that the angle between the mesh and character remains the same.
  // If we set position to 0, 0, then we need to make the characters bounds box move the same way
  // (minus the mesh's position) so that it doesn't get closer.

  Matrix4x4 mat = Matrix4x4::getTrs(collider->getGameObject()->getTransform()->getPosition(),
                          collider->getGameObject()->getTransform()->getRotation(),
                          Vector3(1, 1, 1));
  mat = mat.inverse();

  Vector3 relPos = mat * pos;
  Vector3 extents = bounds.extents;
  extents.y = extents.y / 2.0f; // Set to 20.0f for a large step

  //**********************************************
  Collision collision;
  //collision.relativeVelocity = frameMoveSpeed;

  for(int v = 0; v < vertices.size(); v+=3)
  {
    Vector3 a = vertices.at(v);
    Vector3 b = vertices.at(v+1);
    Vector3 c = vertices.at(v+2);

    if(colliding(relPos, extents, a, b, c) == true)
    {
      ContactPoint contact;

      contact.normal = findNormal(a, b, c);
      contact.thisCollider = this;
      contact.otherCollider = collider;
      contact.a = a;
      contact.b = b;
      contact.c = c;

      collision.contacts.push_back(contact);
    }
  }

  Matrix4x4 rotMat = Matrix4x4::getIdentity();
  rotMat = rotMat.rotate(collider->getGameObject()->getTransform()->getRotation() * -1.0f);

  if(collision.contacts.size() > 0)
  {
    //relPos = handleCollision(collision, relPos, extents);
    //relPos = relPos + (rotMat * handleCollision(collision, relPos, extents));
    relPos = relPos + handleCollision(collision, relPos, extents);
  }
  //*******************************************

  ///////////////////////////////////
  Collision stepCollision;
  Vector3 stepExtents = bounds.extents;
  stepExtents.x = stepExtents.x / 2.0f;
  stepExtents.z = stepExtents.z / 2.0f;
  stepExtents.y = stepExtents.y + 0.01f;

  for(int v = 0; v < vertices.size(); v+=3)
  {
    Vector3 a = vertices.at(v);
    Vector3 b = vertices.at(v+1);
    Vector3 c = vertices.at(v+2);

    if(colliding(relPos, stepExtents, a, b, c) == true)
    {
      ContactPoint contact;

      contact.normal = findNormal(a, b, c);
      contact.thisCollider = this;
      contact.otherCollider = collider;
      contact.a = a;
      contact.b = b;
      contact.c = c;

      stepCollision.contacts.push_back(contact);
    }
  }

  stepExtents.y = stepExtents.y - 0.01f;

  if(stepCollision.contacts.size() > 0)
  {
    grounded = true;
    relPos = relPos + (rotMat * handleStep(stepCollision, relPos, stepExtents));
  }
  else
  {
    //grounded = false;
  }
  ///////////////////////////////////

  mat = mat.inverse();
  getGameObject()->getTransform()->setPosition(mat * relPos);
}

Vector3 CharacterController::handleStep(Collision collision, Vector3 pos, Vector3 bounds)
{
  bool stillColliding = true;
  Vector3 change;

  while(stillColliding == true)
  {
    stillColliding = false;
    change.y += 0.01f;

    for(int i = 0; i < collision.contacts.size(); i++)
    {
      ContactPoint c = collision.contacts.at(i);

      if(colliding(pos + change, bounds, c.a, c.b, c.c) == true)
      {
        stillColliding = true;
      }
    }
  }

  return change;
}

Vector3 CharacterController::handleCollision(Collision collision, Vector3 pos, Vector3 bounds)
{
  bool stillColliding = true;
  Vector3 newPos = pos;
  float amount = 0.0f;
  Vector3 origPos = pos;

  while(stillColliding == true)
  {
    stillColliding = false;
    amount += 0.025f;

    for(int i = 0; i < collision.contacts.size(); i++)
    {
      ContactPoint c = collision.contacts.at(i);
      newPos = pos - (c.normal * amount);

      if(colliding(newPos, bounds, c.a, c.b, c.c) == true)
      {
        stillColliding = true;
      }
      else
      {
        pos = newPos;
        amount = 0.0f;
        collision.contacts.erase(collision.contacts.begin() + i);
        i--;
      }
    }
  }

  return pos - origPos;
  //return pos;
}

Vector3 CharacterController::crossProduct(float *a, float *b)
{
  Vector3 product;

  product.x = (a[1] * b[2]) - (a[2] * b[1]);
  product.y = (a[2] * b[0]) - (a[0] * b[2]);
  product.z = (a[0] * b[1]) - (a[1] * b[0]);

  return product;
}

Vector3 CharacterController::findNormal(Vector3 a, Vector3 b, Vector3 c)
{
  float Vector[3], Vector2[3];

  Vector[0] = c.x - a.x;
  Vector[1] = c.y - a.y;
  Vector[2] = c.z - a.z;

  Vector2[0] = b.x - a.x;
  Vector2[1] = b.y - a.y;
  Vector2[2] = b.z - a.z;

  Vector3 normal = crossProduct(Vector,Vector2);
  normal = normal.getNormalized();

  return normal;
}

bool CharacterController::colliding(Vector3 center, Vector3 half, Vector3 a, Vector3 b, Vector3 c)
{
  float tri[3][3];

  tri[0][0] = a.x;
  tri[0][1] = a.y;
  tri[0][2] = a.z;

  tri[1][0] = b.x;
  tri[1][1] = b.y;
  tri[1][2] = b.z;

  tri[2][0] = c.x;
  tri[2][1] = c.y;
  tri[2][2] = c.z;

  float halfsize[3];
  halfsize[0] = half.x;
  halfsize[1] = half.y;
  halfsize[2] = half.z;

  float _center[3];
  _center[0] = center.x;
  _center[1] = center.y;
  _center[2] = center.z;

  if(triBoxOverlap(_center, halfsize, tri) != 0)
  {
    return true;
  }

  return false;
}

}

}

