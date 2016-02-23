#include "Collider.h"
#include "MeshFilter.h"
#include "GameObject.h"
#include "Mesh.h"
#include "Transform.h"
#include "Matrix4x4.h"
#include "Debug.h"
#include "Exception.h"

#include "buccaneer/AnimatedMeshRenderer.h"
#include "buccaneer/AnimatedMesh.h"

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
  updateBounds();
}

void Collider::updateBounds()
{
  Mesh* mesh = NULL;
  MeshFilter* meshFilter = NULL;

  //bounds = Bounds(Vector3(0, 0, 0), Vector3(2, 2, 2));
  //bounds.debug();
  meshFilter = getGameObject()->getComponent<MeshFilter>();

  if(meshFilter != NULL)
  {
    mesh = meshFilter->getMesh();

    if(mesh != NULL)
    {
      bounds = mesh->getBounds();
    }
  }
  else
  {
    AnimatedMeshRenderer* amr = NULL;
    AnimatedMesh* animatedMesh = NULL;

    amr = getGameObject()->getComponent<AnimatedMeshRenderer>();

    if(amr == NULL)
    {
      throw Exception("Cannot add collider since there is no MeshRenderer or AnimatedMeshRenderer");
    }

    if(amr->getAnimatedMesh() != NULL)
    {
      bounds = amr->getAnimatedMesh()->getBounds();
      //bounds.debug();
    }
  }
}

void Collider::update()
{
  //updateBounds();
}

}

}

