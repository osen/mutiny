#include "MeshCollider.h"
#include "MeshFilter.h"
#include "GameObject.h"
#include "Debug.h"

namespace mutiny
{

namespace engine
{

MeshCollider::~MeshCollider()
{

}

void MeshCollider::awake()
{
  Debug::log("MeshCollider awaken");
  mesh = NULL;

  MeshFilter* meshFilter = getGameObject()->getComponent<MeshFilter>();

  if(meshFilter != NULL)
  {
    mesh = meshFilter->getMesh();
    Debug::log("Added mesh");
  }

  Collider::awake();
}

void MeshCollider::setMesh(Mesh* mesh)
{
  this->mesh = mesh;
}

Mesh* MeshCollider::getMesh()
{
  return mesh;
}

}

}

