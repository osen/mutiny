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
  Material* material = this->material;

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

  if(material == NULL)
  {
    material = Material::defaultMaterial;
    //Debug::log("MeshRenderer set to default material");
  }

  shader = material->getShader();
  material->setPass(0);

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

  material->setMatrix("in_Projection", Camera::getCurrent()->getProjectionMatrix());
  material->setMatrix("in_View", viewMat);
  material->setMatrix("in_Model", modelMat);

  GLint positionAttribId = glGetAttribLocation(shader->programId, "in_Position");

  if(positionAttribId != -1)
  {
    glBindBuffer(GL_ARRAY_BUFFER, mesh->positionBufferId);
    glVertexAttribPointer(positionAttribId, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(positionAttribId);
  }

  GLint uvAttribId = glGetAttribLocation(shader->programId, "in_Uv");

  if(uvAttribId != -1)
  {
    glBindBuffer(GL_ARRAY_BUFFER, mesh->uvBufferId);
    glVertexAttribPointer(uvAttribId, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(uvAttribId);
  }

  glDrawArrays(GL_TRIANGLES, 0, mesh->vertices.size());

  if(positionAttribId != -1)
  {
    glDisableVertexAttribArray(positionAttribId);
  }

  if(uvAttribId != -1)
  {
    glDisableVertexAttribArray(uvAttribId);
  }
}

void MeshRenderer::setMaterial(Material* material)
{
  this->material = material;
}

Material* MeshRenderer::getMaterial()
{
  return material;
}

}

}

