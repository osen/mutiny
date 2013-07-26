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

void Graphics::drawTexture(Rect rect, Texture* texture, Material* material)
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
    material = Material::guiMaterial.get();
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
    0, 0,
    0, 1,
    1, 1,
    1, 1,
    1, 0,
    0, 0
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

}

}

