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

GraphicsCacheEntry* GraphicsCacheEntry::create()
{
  GraphicsCacheEntry* rtn = NULL;

  rtn = Application::getGC()->gc_new<GraphicsCacheEntry>();
  rtn->useCount = 10;

  return rtn;
}

GraphicsCache* GraphicsCache::create()
{
  GraphicsCache* rtn = NULL;

  rtn = Application::getGC()->gc_new<GraphicsCache>();
  rtn->entries = Application::getGC()->gc_list<GraphicsCacheEntry*>();

  return rtn;
}

Mesh* GraphicsCache::matchMesh(std::vector<Rect>& rects, std::vector<Rect>& sourceRects)
{
  for(size_t i = 0; i < entries->size(); i++)
  {
    GraphicsCacheEntry* entry = entries->at(i);
    bool different = false;

    if(rects.size() != entry->rects.size() || sourceRects.size() != entry->sourceRects.size())
    {
      continue;
    }

    for(size_t r = 0; r < entry->rects.size(); r++)
    {
      if(rects.at(r).equals(entry->rects.at(r)) == false)
      {
        different = true;
        break;
      }
    }

    if(different == true)
    {
      continue;
    }

    for(size_t r = 0; r < entry->sourceRects.size(); r++)
    {
      if(sourceRects.at(r).equals(entry->sourceRects.at(r)) == false)
      {
        different = true;
        break;
      }
    }

    if(different == true)
    {
      continue;
    }

    entry->useCount = 10;
    return entry->mesh;
  }

  return NULL;
}

void GraphicsCache::addMesh(std::vector<Rect>& rects, std::vector<Rect>& sourceRects, Mesh* mesh)
{
  GraphicsCacheEntry* entry = GraphicsCacheEntry::create();
  entry->rects = rects;
  entry->sourceRects = sourceRects;
  entry->mesh = mesh;
  entries->push_back(entry);
}

void GraphicsCache::sweepUnused()
{
  for(size_t i = 0; i < entries->size(); i++)
  {
    entries->at(i)->useCount--;

    if(entries->at(i)->useCount <= 0)
    {
      entries->remove_at(i);
      i--;
    }
  }
}

// TODO: Does this need to be re-enabled every draw?
void Graphics::setRenderTarget(RenderTexture* renderTarget)
{
  Application::context->renderTarget = renderTarget;
}

// if material is null, a default material with internal-GUITexture.shader is used.
void Graphics::drawTexture(Rect rect, Texture* texture, Rect sourceRect, Material* material)
{
  std::vector<Rect> rects;
  std::vector<Rect> sourceRects;

  rects.push_back(rect);
  sourceRects.push_back(sourceRect);

  drawTextureBatch(rects, texture, sourceRects, material);
}

void Graphics::drawTextureBatch(std::vector<Rect> rects, Texture* texture, std::vector<Rect> sourceRects, Material* material)
{
  RenderTexture* currentRenderTexture = NULL;

  std::vector<Vector3> vertices;
  std::vector<Vector2> uv;
  std::vector<Color> colors;
  std::vector<int> triangles;

  if(material == NULL)
  {
    // TODO: Use a unique material with MVP set
    //material = Application::context->defaultMaterial;
    material = Application::context->guiMaterial;
    //material = Material::guiMaterial;
    material->setMatrix("in_Projection", Matrix4x4::ortho(0, Screen::getWidth(), Screen::getHeight(), 0, -1, 1));
    material->setMatrix("in_View", Matrix4x4::getIdentity());
    material->setMatrix("in_Model", Matrix4x4::getIdentity());
  }

  if(texture == NULL)
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

  if(Application::context->tempMesh == NULL)
  {
    Application::context->tempMesh = Application::getGC()->gc_new<Mesh>();
  }

  GraphicsCache* cache = Application::context->graphicsCache;
  Mesh* mesh = cache->matchMesh(rects, sourceRects);

  if(mesh == NULL)
  {
    //mesh = Application::context->tempMesh;
    mesh = Application::getGC()->gc_new<Mesh>();
    mesh->setVertices(vertices);
    mesh->setUv(uv);
    //mesh.setColors(colors);

    mesh->setTriangles(triangles, 0);
    cache->addMesh(rects, sourceRects, mesh);
  }

  material->setMainTexture(texture);

  currentRenderTexture = RenderTexture::getActive();
  RenderTexture::setActive(Application::context->renderTarget);

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

  std::vector<Rect> rects;
  std::vector<Rect> sourceRects;

  // Top
  rects.push_back(Rect(rect.x, rect.y, texture->getWidth() * left, texture->getHeight() * top));
  sourceRects.push_back(Rect(0, 0, left, top));
  rects.push_back(Rect(rect.x + (texture->getWidth() * left), rect.y, rect.width - (texture->getWidth() * left) - (texture->getWidth() * right), texture->getHeight() * top));
  sourceRects.push_back(Rect(left, 0, 1.0f - right, top));
  rects.push_back(Rect(rect.x + rect.width - (texture->getWidth() * right), rect.y, texture->getWidth() * right, texture->getHeight() * top));
  sourceRects.push_back(Rect(1.0f - right, 0, 1.0f, top));

  // Bottom
  rects.push_back(Rect(rect.x, rect.y + rect.height - (texture->getHeight() * bottom), texture->getWidth() * left, texture->getHeight() * bottom));
  sourceRects.push_back(Rect(0, 1.0f - bottom, left, 1.0f));
  rects.push_back(Rect(rect.x + (texture->getWidth() * left), rect.y + rect.height - (texture->getHeight() * bottom), rect.width - (texture->getWidth() * left) - (texture->getWidth() * right), texture->getHeight() * bottom));
  sourceRects.push_back(Rect(left, 1.0f - bottom, 1.0f - right, 1.0f));
  rects.push_back(Rect(rect.x + rect.width - (texture->getWidth() * right), rect.y + rect.height - (texture->getHeight() * bottom), texture->getWidth() * right, texture->getHeight() * bottom));
  sourceRects.push_back(Rect(1.0f - right, 1.0f - bottom, 1.0f, 1.0f));

  // Side
  rects.push_back(Rect(rect.x, rect.y + texture->getHeight() * top, texture->getWidth() * left, rect.height - texture->getHeight() * top - texture->getHeight() * bottom));
  sourceRects.push_back(Rect(0, top, left, 1.0f - top));
  rects.push_back(Rect(rect.x + rect.width - texture->getWidth() * right, rect.y + texture->getHeight() * top, texture->getWidth() * right, rect.height - texture->getHeight() * top - texture->getHeight() * bottom));
  sourceRects.push_back(Rect(1.0f - right, top, 1.0f, 1.0f - bottom));
  rects.push_back(Rect(rect.x + texture->getWidth() * left, rect.y + texture->getHeight() * top, rect.width - texture->getWidth() * right - texture->getWidth() * left, rect.height - texture->getHeight() * top - texture->getHeight() * bottom));
  sourceRects.push_back(Rect(left, top, 1.0f - right, 1.0f - top));

  drawTextureBatch(rects, texture, sourceRects, material);
}

void Graphics::drawTexture(Rect rect, Texture* texture, Material* material)
{
  drawTexture(rect, texture, Rect(0, 0, 1, 1), material);
}

void Graphics::drawMeshNow(Mesh* mesh, Matrix4x4 matrix, int materialIndex)
{
  Material* material = NULL;
  Shader* shader = NULL;

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

  material = Application::context->currentMaterial;

  if(material == NULL)
  {
    Debug::log("Material is NULL");
    return;
  }

  material->setMatrix("in_Model", matrix);

  shader = material->getShader();

  if(shader == NULL)
  {
    Debug::log("Shader is NULL");
    return;
  }

  GLuint modelUniformId = material->modelUniformId;

  if(modelUniformId != -1)
  {
    glUniformMatrix4fv(modelUniformId, 1, GL_FALSE, matrix.getValue());
  }

  //GLint positionAttribId = glGetAttribLocation(shader->programId, "in_Position");
  GLint positionAttribId = material->positionId;
  //GLint normalAttribId = glGetAttribLocation(shader->programId, "in_Normal");
  //GLint uvAttribId = glGetAttribLocation(shader->programId, "in_Uv");
  GLint normalAttribId = material->normalId;
  GLint uvAttribId = material->uvId;

  if(positionAttribId != -1)
  {
    glBindBuffer(GL_ARRAY_BUFFER, mesh->positionBufferIds->at(materialIndex)->getGLuint());
    glVertexAttribPointer(positionAttribId, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(positionAttribId);
  }

  if(normalAttribId != -1 && mesh->normalBufferIds->size() > materialIndex)
  {
    glBindBuffer(GL_ARRAY_BUFFER, mesh->normalBufferIds->at(materialIndex)->getGLuint());
    glVertexAttribPointer(normalAttribId, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(normalAttribId);
  }

  if(uvAttribId != -1)
  {
    glBindBuffer(GL_ARRAY_BUFFER, mesh->uvBufferIds->at(materialIndex)->getGLuint());
    glVertexAttribPointer(uvAttribId, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(uvAttribId);
  }

  std::vector<int>& triangles = mesh->getTriangles(materialIndex);
  glDrawArrays(GL_TRIANGLES, 0, triangles.size());

  if(positionAttribId != -1)
  {
    glDisableVertexAttribArray(positionAttribId);
  }

  if(normalAttribId != -1 && mesh->normalBufferIds->size() > materialIndex)
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

