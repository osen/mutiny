#include "Graphics.h"
#include "Screen.h"
#include "Rect.h"
#include "Material.h"
#include "Shader.h"
#include "Matrix4x4.h"
#include "RenderTexture.h"
#include "Gui.h"
#include "Debug.h"

#include <GL/glew.h>

#include <vector>
#include <string>
#include <iostream>

namespace mutiny
{

namespace engine
{

GLuint Graphics::positionBufferId = -1;
GLuint Graphics::uvBufferId = -1;
RenderTexture* Graphics::renderTarget = NULL;

void Graphics::setRenderTarget(RenderTexture* renderTarget)
{
  Graphics::renderTarget = renderTarget;

  if(renderTarget == NULL)
  {
    RenderTexture::disable();
  }
  else
  {
    renderTarget->setEnabled(true);
  }
}

// if material is null, a default material with internal-GUITexture.shader is used.
void Graphics::drawTexture(Rect rect, Texture* texture, Rect sourceRect, Material* material)
{
  // Since the GUI system uses this class, we need to set its matrix.
  // Why does Graphics have no way to set the projection matrix?
  //Matrix4x4 projectionMat = Matrix4x4::ortho(0, Screen::getWidth(), Screen::getHeight(), 0, -1, 1);
  Matrix4x4 projectionMat = Gui::getMatrix();
  float x = (float)rect.x;
  float y = (float)rect.y;
  float xw = (float)rect.x + (float)rect.width;
  float yh = (float)rect.y + (float)rect.height;

  if(material == NULL)
  {
    material = Material::guiMaterial;
  }

  if(texture == NULL)
  {
    Debug::logWarning("Texture is null");
    return;
  }

  GLfloat positions[] = {
    x, y,
    x, yh,
    xw, yh,
    xw, yh,
    xw, y,
    x, y
  };

  GLfloat uv[] = {
    sourceRect.x, sourceRect.y,
    sourceRect.x, sourceRect.height,
    sourceRect.width, sourceRect.height,
    sourceRect.width, sourceRect.height,
    sourceRect.width, sourceRect.y,
    sourceRect.x, sourceRect.y
  };

  GLuint programId = material->getShader()->programId;
  material->setMainTexture(texture);
  material->setPass(0);

  material->setMatrix("in_Projection", projectionMat);
  material->setMatrix("in_View", Matrix4x4::getIdentity());
  material->setMatrix("in_Model", Matrix4x4::getIdentity());

  GLint positionAttributeId = glGetAttribLocation(programId, "in_Position");
  GLint uvAttributeId = glGetAttribLocation(programId, "in_Uv");

  if(positionAttributeId == -1 ||
     uvAttributeId == -1)
  {
    Debug::logError("Error: Shader does not provide required attributes");
    throw std::exception();
  }

  if(positionBufferId == -1)
  {
    glGenBuffers(1, &positionBufferId);
  }

  glBindBuffer(GL_ARRAY_BUFFER, positionBufferId);
  glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(positions[0]), positions, GL_DYNAMIC_DRAW);
  glVertexAttribPointer(positionAttributeId, 2, GL_FLOAT, GL_FALSE, 0, 0);

  if(uvBufferId == -1)
  {
    glGenBuffers(1, &uvBufferId);
  }

  glBindBuffer(GL_ARRAY_BUFFER, uvBufferId);
  glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(uv[0]), uv, GL_DYNAMIC_DRAW);
  glVertexAttribPointer(uvAttributeId, 2, GL_FLOAT, GL_FALSE, 0, 0);

  glEnableVertexAttribArray(positionAttributeId);
  glEnableVertexAttribArray(uvAttributeId);
  glDisable(GL_DEPTH_TEST);
  glCullFace(GL_BACK);
  glDrawArrays(GL_TRIANGLES, 0, 6);
  glCullFace(GL_FRONT);
  glEnable(GL_DEPTH_TEST);
  glDisableVertexAttribArray(positionAttributeId);
  glDisableVertexAttribArray(uvAttributeId);
}

void Graphics::drawTexture(Rect rect, Texture* texture, Rect sourceRect, int leftBorder, int rightBorder, int topBorder, int bottomBorder)
{
  drawTexture(rect, texture, sourceRect, leftBorder, rightBorder, topBorder, bottomBorder, Color(1, 1, 1), NULL);
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

}

}

