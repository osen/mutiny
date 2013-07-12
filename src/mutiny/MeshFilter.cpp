#include "MeshFilter.h"
#include "Debug.h"

namespace mutiny
{

namespace engine
{

MeshFilter::~MeshFilter()
{

}

void MeshFilter::onAwake()
{
  Debug::log("MeshFilter awaken");
  mesh = NULL;
}

void MeshFilter::setMesh(Mesh* mesh)
{
  this->mesh = mesh;
}

Mesh* MeshFilter::getMesh()
{
  return mesh;
}

}

}

