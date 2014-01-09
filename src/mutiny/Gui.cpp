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
#include "Font.h"
#include "Application.h"
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
  return Matrix4x4::getIdentity();
}

void Gui::label(Rect rect, std::string text)
{
  GuiSkin* skin = Application::getInternal()->skin;

  if(skin == NULL)
  {
    skin = Application::getInternal()->defaultGuiSkin.get();
  }

  for(int i = 0; i < text.length(); i++)
  {
    CharacterInfo info;

    if(skin->getButton()->font->getCharacterInfo(text[i], &info) == false)
    {
      continue;
    }

    drawTextureWithTexCoords(Rect(rect.x + (rect.width / 2) - ((info.vert.width * text.length()) / 2) + info.vert.width * i,
                                  rect.y + (rect.height / 2) - (info.vert.height / 2),
                                  info.vert.width,
                                  info.vert.height),
                                  (Texture*)skin->getButton()->font->texture.get(), info.uv);
  }
}

bool Gui::button(Rect rect, std::string text)
{
  GuiSkin* skin = Application::getInternal()->skin;

  if(skin == NULL)
  {
    skin = Application::getInternal()->defaultGuiSkin.get();
  }

  if(rect.contains(Input::getMousePosition()) == true)
  {
    if(Input::getMouseButton(0) == true &&
       rect.contains(Input::mouseDownPosition) == true)
    {
      drawUi(rect, (Texture*)skin->getButton()->getActive()->getBackground(), skin->getButton());
    }
    else if(Input::getMouseButtonUp(0) == true &&
            rect.contains(Input::mouseDownPosition) == true)
    {
      Input::mouseDownPosition = Vector3(-1, -1, -1);
      return true;
    }
    else
    {
      drawUi(rect, (Texture*)skin->getButton()->getHover()->getBackground(), skin->getButton());
    }
  }
  else
  {
    drawUi(rect, (Texture*)skin->getButton()->getNormal()->getBackground(), skin->getButton());
  }

  label(rect, text);

  return false;
}

void Gui::drawTexture(Rect rect, Texture* texture)
{
  Material* guiMaterial = Material::guiMaterial;

  guiMaterial->setMatrix("in_Projection", Matrix4x4::ortho(0, Screen::getWidth(), Screen::getHeight(), 0, -1, 1));
  guiMaterial->setMatrix("in_View", Matrix4x4::getIdentity());
  guiMaterial->setMatrix("in_Model", getMatrix());
  Graphics::drawTexture(rect, texture, guiMaterial);
}

void Gui::drawTextureWithTexCoords(Rect position, Texture* texture, Rect texCoords)
{
  Material* guiMaterial = Material::guiMaterial;

  guiMaterial->setMatrix("in_Projection", Matrix4x4::ortho(0, Screen::getWidth(), Screen::getHeight(), 0, -1, 1));
  guiMaterial->setMatrix("in_View", Matrix4x4::getIdentity());
  guiMaterial->setMatrix("in_Model", getMatrix());
  Graphics::drawTexture(position, texture, texCoords, guiMaterial);
}

void Gui::drawUi(Rect rect, Texture* texture, GuiStyle* style)
{
  Graphics::drawTexture(rect, texture, Rect(0, 0, 1, 1),
                        style->border.left,
                        style->border.right,
                        style->border.top,
                        style->border.bottom);
}

void Gui::box(Rect rect, std::string text)
{
  GuiSkin* skin = Application::getInternal()->skin;

  if(skin == NULL)
  {
    skin = Application::getInternal()->defaultGuiSkin.get();
  }

  drawUi(rect, (Texture*)skin->getBox()->getNormal()->getBackground(), skin->getBox());
  label(rect, text);
}

}

}

