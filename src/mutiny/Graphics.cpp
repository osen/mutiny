#include "Graphics.h"
#include "Screen.h"
#include "Rect.h"
#include "Material.h"
#include "Shader.h"
#include "Matrix4x4.h"
#include "RenderTexture.h"
#include "Gui.h"
#include "Camera.h"
#include "Vector3.h"
#include "GameObject.h"
#include "Transform.h"
#include "Mesh.h"
#include "Debug.h"

#include <GL/glew.h>

#include <vector>
#include <string>
#include <iostream>
#include <string>

namespace mutiny
{

namespace engine
{

Material* Graphics::defaultMaterial;
RenderTexture* Graphics::renderTarget;

// TODO: Does this need to be re-enabled every draw?
void Graphics::setRenderTarget(RenderTexture* renderTarget)
{
  Graphics::renderTarget = renderTarget;
}

// if material is null, a default material with internal-GUITexture.shader is used.
void Graphics::drawTexture(Rect rect, Texture* texture, Rect sourceRect, Material* material)
{
  RenderTexture* currentRenderTexture = NULL;

  std::vector<Vector3> vertices;
  std::vector<Vector2> uv;
  std::vector<Color> colors;
  std::vector<int> triangles;

  float x = (float)rect.x;
  float y = (float)rect.y;
  float xw = (float)rect.x + (float)rect.width;
  float yh = (float)rect.y + (float)rect.height;

  if(material == NULL)
  {
    // TODO: Use a unique material with MVP set
    material = Graphics::defaultMaterial;
    material->setMatrix("in_Projection", Matrix4x4::ortho(0, Screen::getWidth(), Screen::getHeight(), 0, -1, 1));
    material->setMatrix("in_View", Matrix4x4::getIdentity());
    material->setMatrix("in_Model", Matrix4x4::getIdentity());
  }

  if(texture == NULL)
  {
    Debug::logWarning("Texture is null");
    return;
  }

  triangles.push_back(0);
  triangles.push_back(1);
  triangles.push_back(2);
  triangles.push_back(3);
  triangles.push_back(4);
  triangles.push_back(5);

  vertices.push_back(Vector3(x, y, 0));
  vertices.push_back(Vector3(x, yh, 0));
  vertices.push_back(Vector3(xw, yh));
  vertices.push_back(Vector3(xw, yh));
  vertices.push_back(Vector3(xw, y));
  vertices.push_back(Vector3(x, y));

  uv.push_back(Vector2(sourceRect.x, sourceRect.y));
  uv.push_back(Vector2(sourceRect.x, sourceRect.height));
  uv.push_back(Vector2(sourceRect.width, sourceRect.height));
  uv.push_back(Vector2(sourceRect.width, sourceRect.height));
  uv.push_back(Vector2(sourceRect.width, sourceRect.y));
  uv.push_back(Vector2(sourceRect.x, sourceRect.y));

  Mesh mesh;
  mesh.setVertices(vertices);
  mesh.setUv(uv);
  //mesh.setColors(colors);

  mesh.setTriangles(triangles, 0);

  material->setMainTexture(texture);
  material->setPass(0);

  currentRenderTexture = RenderTexture::getActive();
  RenderTexture::setActive(Graphics::renderTarget);

  glDisable(GL_DEPTH_TEST);
  glCullFace(GL_BACK);
  drawMeshNow(&mesh, 0);
  glCullFace(GL_FRONT);
  glEnable(GL_DEPTH_TEST);

  RenderTexture::setActive(currentRenderTexture);
}

void Graphics::drawTexture(Rect rect, Texture* texture, Rect sourceRect, int leftBorder, int rightBorder, int topBorder, int bottomBorder, Material* material)
{
  drawTexture(rect, texture, sourceRect, leftBorder, rightBorder, topBorder, bottomBorder, Color(1, 1, 1), material);
}

void Graphics::drawTexture(Rect rect, Texture* texture, Rect sourceRect, int leftBorder, int rightBorder, int topBorder, int bottomBorder, Color color, Material* material)
{
  float left = 1.0f / (float)leftBorder;
  float right = 1.0f / (float)rightBorder;
  float top = 1.0f / (float)topBorder;
  float bottom = 1.0f / (float)bottomBorder;

  // Top
  drawTexture(Rect(rect.x, rect.y, texture->getWidth() * left, texture->getHeight() * top), texture, Rect(0, 0, left, top), material);
  drawTexture(Rect(rect.x + (texture->getWidth() * left), rect.y, rect.width - (texture->getWidth() * left) - (texture->getWidth() * right), texture->getHeight() * top), texture, Rect(left, 0, 1.0f - right, top), material);
  drawTexture(Rect(rect.x + rect.width - (texture->getWidth() * right), rect.y, texture->getWidth() * right, texture->getHeight() * top), texture, Rect(1.0f - right, 0, 1.0f, top), material);

  // Bottom
  drawTexture(Rect(rect.x, rect.y + rect.height - (texture->getHeight() * bottom), texture->getWidth() * left, texture->getHeight() * bottom), texture, Rect(0, 1.0f - bottom, left, 1.0f), material);
  drawTexture(Rect(rect.x + (texture->getWidth() * left), rect.y + rect.height - (texture->getHeight() * bottom), rect.width - (texture->getWidth() * left) - (texture->getWidth() * right), texture->getHeight() * bottom), texture, Rect(left, 1.0f - bottom, 1.0f - right, 1.0f), material);
  drawTexture(Rect(rect.x + rect.width - (texture->getWidth() * right), rect.y + rect.height - (texture->getHeight() * bottom), texture->getWidth() * right, texture->getHeight() * bottom), texture, Rect(1.0f - right, 1.0f - bottom, 1.0f, 1.0f), material);

  // Side
  drawTexture(Rect(rect.x, rect.y + texture->getHeight() * top, texture->getWidth() * left, rect.height - texture->getHeight() * top - texture->getHeight() * bottom), texture, Rect(0, top, left, 1.0f - top), material);
  drawTexture(Rect(rect.x + rect.width - texture->getWidth() * right, rect.y + texture->getHeight() * top, texture->getWidth() * right, rect.height - texture->getHeight() * top - texture->getHeight() * bottom), texture, Rect(1.0f - right, top, 1.0f, 1.0f - bottom), material);
  drawTexture(Rect(rect.x + texture->getWidth() * left, rect.y + texture->getHeight() * top, rect.width - texture->getWidth() * right - texture->getWidth() * left, rect.height - texture->getHeight() * top - texture->getHeight() * bottom), texture, Rect(left, top, 1.0f - right, 1.0f - top), material);
}

void Graphics::drawTexture(Rect rect, Texture* texture, Material* material)
{
  drawTexture(rect, texture, Rect(0, 0, 1, 1), material);
}

void Graphics::drawMeshNow(Mesh* mesh, Matrix4x4 matrix, int materialIndex)
{
  Material* material;

  material = Material::current;
  material->setMatrix("in_Model", matrix);

  drawMeshNow(mesh, materialIndex);
}

void Graphics::drawMeshNow(Mesh* mesh, int materialIndex)
{
  Material* material;
  Shader* shader;

  if(mesh == NULL)
  {
    Debug::log("Mesh is null");
    return;
  }

  if(materialIndex >= mesh->getSubmeshCount())
  {
    Debug::log("Invalid material index");
    return;
  }

  material = Material::current;

  if(material == NULL)
  {
    Debug::log("Material is NULL");
    return;
  }

  shader = material->getShader();

  if(shader == NULL)
  {
    Debug::log("Shader is NULL");
    return;
  }

  GLint positionAttribId = glGetAttribLocation(shader->programId, "in_Position");
  GLint uvAttribId = glGetAttribLocation(shader->programId, "in_Uv");

  if(positionAttribId != -1)
  {
    glBindBuffer(GL_ARRAY_BUFFER, mesh->positionBufferIds.at(materialIndex));
    glVertexAttribPointer(positionAttribId, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(positionAttribId);
  }

  if(uvAttribId != -1)
  {
    glBindBuffer(GL_ARRAY_BUFFER, mesh->uvBufferIds.at(materialIndex));
    glVertexAttribPointer(uvAttribId, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(uvAttribId);
  }

  material->apply();
  glDrawArrays(GL_TRIANGLES, 0, mesh->getTriangles(materialIndex)->size());

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

}

