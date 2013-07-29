#include "Gui.h"
#include "Screen.h"
#include "Rect.h"
#include "Material.h"
#include "Shader.h"
#include "Camera.h"
#include "Vector3.h"
#include "Graphics.h"
#include "GuiSkin.h"
#include "GuiStyle.h"
#include "GuiStyleState.h"
#include "Input.h"
#include "Debug.h"

#include <GL/glew.h>

#include <vector>
#include <string>
#include <iostream>

namespace mutiny
{

namespace engine
{

GuiSkin* Gui::skin = NULL;

Matrix4x4 Gui::getMatrix()
{
  return Matrix4x4::ortho(0, Screen::getWidth(), Screen::getHeight(), 0, -1, 1);
}

void Gui::label(Rect rect, std::string text)
{

}

bool Gui::button(Rect rect, std::string text)
{
  GuiSkin* skin = Gui::skin;

  if(skin == NULL)
  {
    skin = GuiSkin::defaultGuiSkin.get();
  }

  if(rect.contains(Input::getMousePosition()) == true)
  {
    if(Input::getMouseButton(0) == true &&
       rect.contains(Input::mouseDownPosition) == true)
    {
      drawTexture(rect, (Texture*)skin->getButton()->getActive()->getBackground());
    }
    else if(Input::getMouseButtonUp(0) == true &&
            rect.contains(Input::mouseDownPosition) == true)
    {
      return true;
    }
    else
    {
      drawTexture(rect, (Texture*)skin->getButton()->getHover()->getBackground());
    }
  }
  else
  {
    drawTexture(rect, (Texture*)skin->getButton()->getNormal()->getBackground());
  }


  return false;
}

void Gui::drawTexture(Rect rect, Texture* texture)
{
  Material* guiMaterial = Material::guiMaterial;

  guiMaterial->setMatrix("in_Projection", getMatrix());
  Graphics::drawTexture(rect, texture, guiMaterial);
}

void Gui::box(Rect rect, std::string text)
{
  //drawTexture(rect, NULL);
}

}

}

