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

  updateBounds();
}

void Collider::updateBounds()
{
  Mesh* mesh = NULL;
  MeshFilter* meshFilter = NULL;

  bounds = Bounds(Vector3(0, 0, 0), Vector3(2, 2, 2));
  meshFilter = getGameObject()->getComponent<MeshFilter>();

  if(meshFilter != NULL)
  {
    mesh = meshFilter->getMesh();

    if(mesh != NULL)
    {
      bounds = mesh->getBounds();
    }
  }
}

void Collider::update()
{
  //updateBounds();
}

}

}

