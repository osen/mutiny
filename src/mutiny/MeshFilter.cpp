#include "MeshFilter.h"
#include "Debug.h"

namespace mutiny
{

namespace engine
{

MeshFilter::~MeshFilter()
{

}

void MeshFilter::setMesh(arc<Mesh> mesh)
{
  this->mesh = mesh;
}

arc<Mesh> MeshFilter::getMesh()
{
  return mesh;
}

}

}

