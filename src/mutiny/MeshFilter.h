#ifndef MUTINY_ENGINE_MESHFILTER_H
#define MUTINY_ENGINE_MESHFILTER_H

#include "ref.h"
#include "Behaviour.h"

namespace mutiny
{

namespace engine
{

class Mesh;

class MeshFilter : public Behaviour
{
public:
  virtual ~MeshFilter();

  void setMesh(ref<Mesh> mesh);
  ref<Mesh> getMesh();

private:
  ref<Mesh> mesh;

};

}

}

#endif

