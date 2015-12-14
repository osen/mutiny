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

arc<Material> Graphics::defaultMaterial;
arc<RenderTexture> Graphics::renderTarget;

// TODO: Does this need to be re-enabled every draw?
void Graphics::setRenderTarget(arc<RenderTexture> renderTarget)
{
  Graphics::renderTarget = renderTarget;
}

// if material is null, a default material with internal-GUITexture.shader is used.
void Graphics::drawTexture(Rect rect, arc<Texture> texture, Rect sourceRect, arc<Material> material)
{
  std::vector<Rect> rects;
  std::vector<Rect> sourceRects;

  rects.push_back(rect);
  sourceRects.push_back(sourceRect);

  drawTextureBatch(rects, texture, sourceRects, material);
}

void Graphics::drawTextureBatch(std::vector<Rect> rects, arc<Texture> texture, std::vector<Rect> sourceRects, arc<Material> material)
{
  arc<RenderTexture> currentRenderTexture;

  std::vector<Vector3> vertices;
  std::vector<Vector2> uv;
  std::vector<Color> colors;
  std::vector<int> triangles;

  if(material.get() == NULL)
  {
    // TODO: Use a unique material with MVP set
    material = Graphics::defaultMaterial;
    //material = Material::guiMaterial;
    material->setMatrix("in_Projection", Matrix4x4::ortho(0, Screen::getWidth(), Screen::getHeight(), 0, -1, 1));
    material->setMatrix("in_View", Matrix4x4::getIdentity());
    material->setMatrix("in_Model", Matrix4x4::getIdentity());
  }

  if(texture.get() == NULL)
  {
    Debug::logWarning("Texture is null");
    return;
  }

  for(int i = 0; i < rects.size(); i++)
  {
    float x = (float)rects.at(i).x;
    float y = (float)rects.at(i).y;
    float xw = (float)rects.at(i).x + (float)rects.at(i).width;
    float yh = (float)rects.at(i).y + (float)rects.at(i).height;

    triangles.push_back((i*6) + 0);
    triangles.push_back((i*6) + 1);
    triangles.push_back((i*6) + 2);
    triangles.push_back((i*6) + 3);
    triangles.push_back((i*6) + 4);
    triangles.push_back((i*6) + 5);

    vertices.push_back(Vector3(x, y, 0));
    vertices.push_back(Vector3(x, yh, 0));
    vertices.push_back(Vector3(xw, yh));
    vertices.push_back(Vector3(xw, yh));
    vertices.push_back(Vector3(xw, y));
    vertices.push_back(Vector3(x, y));

    uv.push_back(Vector2(sourceRects.at(i).x, sourceRects.at(i).y));
    uv.push_back(Vector2(sourceRects.at(i).x, sourceRects.at(i).height));
    uv.push_back(Vector2(sourceRects.at(i).width, sourceRects.at(i).height));
    uv.push_back(Vector2(sourceRects.at(i).width, sourceRects.at(i).height));
    uv.push_back(Vector2(sourceRects.at(i).width, sourceRects.at(i).y));
    uv.push_back(Vector2(sourceRects.at(i).x, sourceRects.at(i).y));
  }

  arc<Mesh> mesh = arc<Mesh>::alloc();
  mesh->setVertices(vertices);
  mesh->setUv(uv);
  //mesh.setColors(colors);

  mesh->setTriangles(triangles, 0);
  material->setMainTexture(texture);

  currentRenderTexture = RenderTexture::getActive();
  RenderTexture::setActive(Graphics::renderTarget);

  glDisable(GL_DEPTH_TEST);
  glCullFace(GL_BACK);

  for(int i = 0; i < material->getPassCount(); i++)
  {
    material->setPass(i, material);
    // HACK: A matrix is required to be passed into drawMeshNow.
    drawMeshNow(mesh, material->getMatrix("in_Model"), 0);
  }

  glCullFace(GL_FRONT);
  glEnable(GL_DEPTH_TEST);

  RenderTexture::setActive(currentRenderTexture);
}

void Graphics::drawTexture(Rect rect, arc<Texture> texture, Rect sourceRect, int leftBorder, int rightBorder, int topBorder, int bottomBorder, arc<Material> material)
{
  drawTexture(rect, texture, sourceRect, leftBorder, rightBorder, topBorder, bottomBorder, Color(1, 1, 1), material);
}

void Graphics::drawTexture(Rect rect, arc<Texture> texture, Rect sourceRect, int leftBorder, int rightBorder, int topBorder, int bottomBorder, Color color, arc<Material> material)
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

void Graphics::drawTexture(Rect rect, arc<Texture> texture, arc<Material> material)
{
  drawTexture(rect, texture, Rect(0, 0, 1, 1), material);
}

void Graphics::drawMeshNow(arc<Mesh> mesh, Matrix4x4 matrix, int materialIndex)
{
  arc<Material> material;
  arc<Shader> shader;

  if(mesh.get() == NULL)
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

  if(material.get() == NULL)
  {
    Debug::log("Material is NULL");
    return;
  }

  shader = material->getShader();

  if(shader.get() == NULL)
  {
    Debug::log("Shader is NULL");
    return;
  }

  GLuint modelUniformId = glGetUniformLocation(shader->programId, "in_Model");

  if(modelUniformId != -1)
  {
    //material->setMatrix("in_Model", matrix);
    glUniformMatrix4fv(modelUniformId, 1, GL_FALSE, matrix.getValue());
  }

  GLint positionAttribId = glGetAttribLocation(shader->programId, "in_Position");
  GLint normalAttribId = glGetAttribLocation(shader->programId, "in_Normal");
  GLint uvAttribId = glGetAttribLocation(shader->programId, "in_Uv");

  if(positionAttribId != -1)
  {
    glBindBuffer(GL_ARRAY_BUFFER, mesh->positionBufferIds.at(materialIndex)->id);
    glVertexAttribPointer(positionAttribId, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(positionAttribId);
  }

  if(normalAttribId != -1 && mesh->normalBufferIds.size() > materialIndex)
  {
    glBindBuffer(GL_ARRAY_BUFFER, mesh->normalBufferIds.at(materialIndex)->id);
    glVertexAttribPointer(normalAttribId, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(normalAttribId);
  }

  if(uvAttribId != -1)
  {
    glBindBuffer(GL_ARRAY_BUFFER, mesh->uvBufferIds.at(materialIndex)->id);
    glVertexAttribPointer(uvAttribId, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(uvAttribId);
  }

  std::vector<int>& triangles = mesh->getTriangles(materialIndex);
  glDrawArrays(GL_TRIANGLES, 0, triangles.size());

  if(positionAttribId != -1)
  {
    glDisableVertexAttribArray(positionAttribId);
  }

  if(normalAttribId != -1 && mesh->normalBufferIds.size() > materialIndex)
  {
    glDisableVertexAttribArray(normalAttribId);
  }

  if(uvAttribId != -1)
  {
    glDisableVertexAttribArray(uvAttribId);
  }
}

}

}

