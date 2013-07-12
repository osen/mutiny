#include "Collider.h"
#include "MeshFilter.h"
#include "GameObject.h"
#include "Mesh.h"
#include "Transform.h"
#include "Matrix4x4.h"
#include "Debug.h"

#include <sstream>

namespace mutiny
{

namespace engine
{

Collider::Collider() : bounds(Vector3(), Vector3())
{

}

Collider::~Collider()
{

}

Bounds Collider::getBounds()
{
  return bounds;
}

void Collider::awake()
{
  Debug::log("Collider awaken");
  Mesh* mesh = NULL;

  MeshFilter* meshFilter = getGameObject()->getComponent<MeshFilter>();

  if(meshFilter != NULL)
  {
    mesh = meshFilter->getMesh();

    if(mesh != NULL)
    {
      bounds = mesh->getBounds();
      //std::stringstream ss;
      //ss << "Collider set bounds from mesh" << std::endl;
      //ss << "x: " << bounds.center.x << " y: " << bounds.center.y << " z: " << bounds.center.z << std::endl;
      //ss << "x: " << bounds.size.x << " y: " << bounds.size.y << " z: " << bounds.size.z;
      //Debug::log(ss.str());
    }
  }

  lastPosition = getGameObject()->getTransform()->getPosition();
}

void Collider::updateBounds()
{
  Transform* transform = getGameObject()->getComponent<Transform>();

  if(transform != NULL)
  {
    //Matrix4x4 mat = Matrix4x4::getIdentity();
    //mat = mat.translate(transform->getPosition());
    //Vector3 vec = Vector3();
    //vec = mat * vec;
    //bounds.center = vec;
    bounds.center = transform->getPosition();
    bounds.min = bounds.center - bounds.extents;
    bounds.max = bounds.center + bounds.extents;
  }

/*
  Matrix4x4 tst = Matrix4x4::getIdentity();
  tst = tst.translate(Vector3(0, -10, 0));

  Vector3 tmp(100, 100, 100);
  tmp = tst * tmp;
  std::stringstream ss;

  ss << tmp.y << std::endl;
  Debug::log(ss.str());
*/
}

void Collider::update()
{
  updateBounds();
  lastPosition = getGameObject()->getTransform()->getPosition();
}

}

}

