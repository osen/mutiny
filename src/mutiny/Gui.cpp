#include "Gui.h"
#include "Screen.h"
#include "Rect.h"
#include "Material.h"
#include "Shader.h"
#include "Camera.h"
#include "Vector3.h"
#include "Graphics.h"
#include "Debug.h"

#include <GL/glew.h>

#include <vector>
#include <string>
#include <iostream>

namespace mutiny
{

namespace engine
{

Matrix4x4 Gui::getMatrix()
{
  return Matrix4x4::ortho(0, Screen::getWidth(), Screen::getHeight(), 0, -1, 1);
}

bool Gui::button(Rect rect, std::string text)
{
  return false;
}

void Gui::drawTexture(Rect rect, Texture* texture)
{
  Material* guiMaterial = Material::guiMaterial.get();

  guiMaterial->setMatrix("in_Projection", getMatrix());
  Graphics::drawTexture(rect, texture, guiMaterial);
}

void Gui::box(Rect rect, std::string text)
{
  //drawTexture(rect, NULL);
}

}

}

