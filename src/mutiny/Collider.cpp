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
  ref<Mesh> mesh;
  ref<MeshFilter> meshFilter;

  //bounds = Bounds(Vector3(0, 0, 0), Vector3(2, 2, 2));
  //bounds.debug();
  meshFilter = getGameObject()->getComponent<MeshFilter>();

  if(meshFilter.valid())
  {
    mesh = meshFilter->getMesh();

    if(mesh.valid())
    {
      bounds = mesh->getBounds();
    }
  }
  else
  {
    ref<AnimatedMeshRenderer> amr;
    ref<AnimatedMesh> animatedMesh;

    amr = getGameObject()->getComponent<AnimatedMeshRenderer>();

    if(amr.expired())
    {
      throw Exception("Cannot add collider since there is no MeshRenderer or AnimatedMeshRenderer");
    }

    if(amr->getAnimatedMesh().valid())
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

