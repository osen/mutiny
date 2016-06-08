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

MeshRenderer::MeshRenderer()
{

}

MeshRenderer::~MeshRenderer()
{

}

void MeshRenderer::render()
{
  ref<MeshFilter> meshFilter = getGameObject()->getComponent<MeshFilter>();
  ref<Mesh> mesh;
  ref<Transform> transform = getGameObject()->getTransform();

  if(transform.expired())
  {
    Debug::log("Failed to find Transform");
    return;
  }

  if(meshFilter.expired())
  {
    Debug::log("Failed to find MeshFilter");
    return;
  }

  mesh = meshFilter->getMesh();

  if(mesh.expired())
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

  for(size_t i = 0; i < mesh->getSubmeshCount(); i++)
  {
    ref<Material> material = getMaterial();

    if(materials.size() > i)
    {
      material = materials.at(i);
    }

    if(material.expired())
    {
      if(mesh->getNormals().size() > 0 && mesh->getUv().size() > 0)
      {
        material = Application::context->meshNormalTextureMaterial;
        material->setMainTexture(Application::context->defaultTexture);
      }
      else if(mesh->getNormals().size() > 0)
      {
        material = Application::context->meshNormalMaterial;
      }
      else
      {
        material = Application::context->meshNormalMaterial;
      }
    }

    material->setMatrix("in_Projection", Camera::getCurrent()->getProjectionMatrix());
    material->setMatrix("in_View", viewMat);
    material->setMatrix("in_NormalMatrix", (viewMat * modelMat.inverse()).transpose());

    for(size_t j = 0; j < material->getPassCount(); j++)
    {
      material->setPass(j, material.get());
      Graphics::drawMeshNow(mesh, modelMat, i);
    }
  }
}

void MeshRenderer::setMaterials(std::vector<ref<Material> > materials)
{
  this->materials = materials;
}

void MeshRenderer::setMaterial(ref<Material> material)
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

ref<Material> MeshRenderer::getMaterial()
{
  if(materials.size() < 1)
  {
    return NULL;
  }

  return materials.at(0).get();
}

std::vector<ref<Material> > MeshRenderer::getMaterials()
{
  return materials;
}

}

}

