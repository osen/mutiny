#include "MeshRenderer.h"
#include "MeshFilter.h"
#include "Mesh.h"
#include "GameObject.h"
#include "Material.h"
#include "Camera.h"
#include "Shader.h"
#include "Transform.h"
#include "Debug.h"

#include <memory>
#include <functional>

namespace mutiny
{

namespace engine
{

MeshRenderer::~MeshRenderer()
{

}

void MeshRenderer::awake()
{
}

void MeshRenderer::render()
{
  MeshFilter* meshFilter = getGameObject()->getComponent<MeshFilter>();
  Mesh* mesh = NULL;
  Shader* shader = NULL;
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

    if(materials.size() > i)
    {
      material = materials[i];
    }

    if(material == NULL)
    {
      material = Material::defaultMaterial;
      //Debug::log("MeshRenderer set to default material");
    }

    shader = material->getShader();
    GLint positionAttribId = glGetAttribLocation(shader->programId, "in_Position");
    GLint uvAttribId = glGetAttribLocation(shader->programId, "in_Uv");

    material->setMatrix("in_Projection", Camera::getCurrent()->getProjectionMatrix());
    material->setMatrix("in_View", viewMat);
    material->setMatrix("in_Model", modelMat);

    material->setPass(0);

    if(positionAttribId != -1)
    {
      glBindBuffer(GL_ARRAY_BUFFER, mesh->positionBufferIds.at(i));
      glVertexAttribPointer(positionAttribId, 3, GL_FLOAT, GL_FALSE, 0, 0);
      glEnableVertexAttribArray(positionAttribId);
    }

    if(uvAttribId != -1)
    {
      glBindBuffer(GL_ARRAY_BUFFER, mesh->uvBufferIds.at(i));
      glVertexAttribPointer(uvAttribId, 2, GL_FLOAT, GL_FALSE, 0, 0);
      glEnableVertexAttribArray(uvAttribId);
    }

    //glDrawArrays(GL_TRIANGLES, 0, mesh->vertices.size());
    glDrawArrays(GL_TRIANGLES, 0, mesh->getTriangles(i)->size());

    if(positionAttribId != -1)
    {
      glDisableVertexAttribArray(positionAttribId);
    }

    if(uvAttribId != -1)
    {
      glDisableVertexAttribArray(uvAttribId);
    }
  }
}

void MeshRenderer::setMaterials(std::vector<Material*> materials)
{
  this->materials = materials;
}

void MeshRenderer::setMaterial(Material* material)
{
  if(materials.size() < 1)
  {
    materials.push_back(NULL);
  }

  materials[0] = material;
}

Material* MeshRenderer::getMaterial()
{
  if(materials.size() < 1)
  {
    return NULL;
  }

  return materials[0];
}

void MeshRenderer::getMaterials(std::vector<Material*>* materials)
{
  for(int i = 0; i < this->materials.size(); i++)
  {
    materials->push_back(this->materials.at(i));
  }
}

}

}

