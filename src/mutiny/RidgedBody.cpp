#include "RidgedBody.h"
#include "GameObject.h"
#include "Transform.h"
#include "Vector3.h"
#include "Time.h"
#include "Bounds.h"
#include "MeshCollider.h"
#include "Matrix4x4.h"
#include "Mesh.h"

#include "internal/tribox.h"

#include <iostream>

namespace mutiny
{

namespace engine
{

RidgedBody::RidgedBody()
{

}

RidgedBody::~RidgedBody()
{

}

void RidgedBody::update()
{
  getGameObject()->getTransform()->translate(Vector3(0, -10, 0) * Time::getDeltaTime());
  std::vector<Object*> collidableObjects = GameObject::findObjectsOfType<MeshCollider>();

  for(int i = 0; i < collidableObjects.size(); i++)
  {
    MeshCollider* meshCollider = ((MeshCollider*)collidableObjects.at(i));
    Vector3 position = getGameObject()->getTransform()->getPosition();
    arc<Mesh> mesh = meshCollider->getMesh();
    std::vector<Vector3>& vertices = mesh->getVertices();

    Matrix4x4 colliderItrs = Matrix4x4::getTrs(meshCollider->getGameObject()->getTransform()->getPosition(),
     meshCollider->getGameObject()->getTransform()->getRotation(), Vector3(1, 1, 1)).inverse();

    position = colliderItrs * position;
    //Vector3 size = Bounds(Vector3(), Vector3(1, 1, 1)).extents;
    Vector3 size = Vector3(1, 1, 1);

    bool isColliding = false;

    for(int v = 0; v < vertices.size(); v+=3)
    {
      Vector3 a = vertices.at(v);
      Vector3 b = vertices.at(v+1);
      Vector3 c = vertices.at(v+2);

      if(colliding(position, size, a, b, c) == true)
      {
        isColliding = true;
        break;
      }
    }

    if(isColliding == true)
    {
      bool found = false;
      for(int c = 0; c < collisions.size(); c++)
      {
        if(collisions.at(c).collider == meshCollider)
        {
          //std::cout << "Stay" << std::endl;
          getGameObject()->collisionStay(collisions.at(c));
          found = true;
          break;
        }
      }

      if(found == false)
      {
        Collision collision;
        collision.collider = meshCollider;
        collisions.push_back(collision);
        //std::cout << "Enter" << std::endl;
        getGameObject()->collisionEnter(collision);
      }
    }
    else
    {
      for(int c = 0; c < collisions.size(); c++)
      {
        if(collisions.at(c).collider == meshCollider)
        {
          //std::cout << "Exit" << std::endl;
          getGameObject()->collisionExit(collisions.at(c));
          collisions.erase(collisions.begin() + c);
          break;
        }
      }
    }
  }
}

bool RidgedBody::colliding(Vector3& center, Vector3& half, Vector3& a, Vector3& b, Vector3& c)
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

