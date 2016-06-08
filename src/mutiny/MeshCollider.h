#ifndef MUTINY_ENGINE_MESHCOLLIDER_H
#define MUTINY_ENGINE_MESHCOLLIDER_H

#include "Collider.h"
#include "ref.h"

namespace mutiny
{

namespace engine
{

class Mesh;
class GameObject;

class MeshCollider : public Collider
{
  friend class mutiny::engine::GameObject;

public:
  virtual ~MeshCollider();

  void setMesh(ref<Mesh> mesh);
  ref<Mesh> getMesh();

private:
  ref<Mesh> mesh;

  virtual void awake();

};

}

}

#endif

