#include "MeshRenderer.h"
#include "MeshFilter.h"
#include "Mesh.h"
#include "GameObject.h"
#include "Material.h"
#include "Camera.h"
#include "Shader.h"
#include "Transform.h"
#include "Graphics.h"
#include "Debug.h"
#include "Texture2d.h"

#include <memory>
#include <functional>

namespace mutiny
{

namespace engine
{

MeshRenderer::~MeshRenderer()
{

}

void MeshRenderer::render()
{
  MeshFilter* meshFilter = getGameObject()->getComponent<MeshFilter>();
  arc<Mesh> mesh;
  Transform* transform = getGameObject()->getTransform();

  if(transform == NULL)
  {
    Debug::log("Failed to find Transform");
    return;
  }

  if(meshFilter == NULL)
  {
    Debug::log("Failed to find MeshFilter");
    return;
  }

  mesh = meshFilter->getMesh();

  if(mesh.get() == NULL)
  {
    Debug::log("No mesh bound");
    return;
  }

  // obtain left-handed coordinate system by multiplying a negative Z scale on ModelView matrix

  Matrix4x4 viewMat = Matrix4x4::getTrs(
    Camera::getCurrent()->getGameObject()->getTransform()->getPosition(),
    Camera::getCurrent()->getGameObject()->getTransform()->getRotation(),
    Vector3(1, 1, 1) * Vector3(1, 1, -1)
  ).inverse();

  Matrix4x4 modelMat = Matrix4x4::getTrs(
    transform->getPosition(),
    transform->getRotation(),
    Vector3(1, 1, 1) * Vector3(1, 1, 1)
  );

  for(int i = 0; i < mesh->getSubmeshCount(); i++)
  {
    arc<Material> material = getMaterial();

    if(materials.size() > i)
    {
      material = materials.at(i);
    }

    if(material.get() == NULL)
    {
      if(mesh->getNormals().size() > 0 && mesh->getUv().size() > 0)
      {
        material = Material::meshNormalTextureMaterial;
        material->setMainTexture(Texture2d::defaultTexture.cast<Texture>());
      }
      else if(mesh->getNormals().size() > 0)
      {
        material = Material::meshNormalMaterial;
      }
      else
      {
        material = Material::meshNormalMaterial;
      }
    }

    material->setMatrix("in_Projection", Camera::getCurrent()->getProjectionMatrix());
    material->setMatrix("in_View", viewMat);
    material->setMatrix("in_NormalMatrix", (viewMat * modelMat.inverse()).transpose());

    for(int j = 0; j < material->getPassCount(); j++)
    {
      material->setPass(j, material);
      Graphics::drawMeshNow(mesh, modelMat, i);
    }
  }
}

void MeshRenderer::setMaterials(std::vector<arc<Material> > materials)
{
  this->materials = materials;
}

void MeshRenderer::setMaterial(arc<Material> material)
{
  if(materials.size() < 1)
  {
    materials.push_back(material);
  }
  else
  {
    materials.at(0) = material;
  }
}

arc<Material> MeshRenderer::getMaterial()
{
  if(materials.size() < 1)
  {
    return arc<Material>();
  }

  return materials.at(0);
}

void MeshRenderer::getMaterials(std::vector<arc<Material> >& materials)
{
  for(int i = 0; i < this->materials.size(); i++)
  {
    materials.push_back(this->materials.at(i));
  }
}

}

}

