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
  materials = Application::getGC()->gc_list<Material*>();
}

MeshRenderer::~MeshRenderer()
{

}

void MeshRenderer::render()
{
  MeshFilter* meshFilter = getGameObject()->getComponent<MeshFilter>();
  Mesh* mesh;
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

  if(mesh == NULL)
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
    Material* material = getMaterial();

    if(materials->size() > i)
    {
      material = materials->at(i);
    }

    if(material == NULL)
    {
      if(mesh->getNormals().size() > 0 && mesh->getUv().size() > 0)
      {
        material = Application::context->meshNormalTextureMaterial;
        material->setMainTexture(Application::context->defaultTexture);
      }
      else if(mesh->getNormals().size() > 0)
      {
        material = material = Application::context->meshNormalMaterial;
      }
      else
      {
        material = material = Application::context->meshNormalMaterial;
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

void MeshRenderer::setMaterials(internal::gc::list<Material*>* materials)
{
  this->materials = materials;
}

void MeshRenderer::setMaterial(Material* material)
{
  if(materials->size() < 1)
  {
    materials->push_back(material);
  }
  else
  {
    materials->at(0) = material;
  }
}

Material* MeshRenderer::getMaterial()
{
  if(materials->size() < 1)
  {
    return NULL;
  }

  return materials->at(0);
}

internal::gc::list<Material*>* MeshRenderer::getMaterials()
{
  return materials;
}

}

}

