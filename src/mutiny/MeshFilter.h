#ifndef MUTINY_ENGINE_MESHFILTER_H
#define MUTINY_ENGINE_MESHFILTER_H

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

  void setMesh(arc<Mesh> mesh);
  arc<Mesh> getMesh();

private:
  arc<Mesh> mesh;

};

}

}

#endif

