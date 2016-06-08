#include "MeshFilter.h"
#include "Debug.h"
#include "Mesh.h"

namespace mutiny
{

namespace engine
{

MeshFilter::~MeshFilter()
{

}

void MeshFilter::setMesh(ref<Mesh> mesh)
{
  this->mesh = mesh;
}

ref<Mesh> MeshFilter::getMesh()
{
  return mesh;
}

}

}

