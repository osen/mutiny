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
#include "Texture.h"
#include "TextAnchor.h"

#include <GL/glew.h>

#include <vector>
#include <string>
#include <iostream>

namespace mutiny
{

namespace engine
{

GuiSkin* Gui::skin;
Matrix4x4 Gui::matrix;

Matrix4x4 Gui::getMatrix()
{
  return matrix;
}

void Gui::setMatrix(Matrix4x4 matrix)
{
  Gui::matrix = matrix;
}

void Gui::label(Rect rect, std::string text)
{
  GuiSkin* skin = Gui::skin;

  if(skin == NULL)
  {
    skin = GuiSkin::_default;
  }

  std::vector<Rect> positions;
  std::vector<Rect> uvs;

  for(int i = 0; i < text.length(); i++)
  {
    CharacterInfo info;
    int padding = 0;

    if(skin->getButton()->getAlignment() == TextAnchor::MiddleLeft)
    {
      padding = 10;
    }

    if(skin->getButton()->font->getCharacterInfo(text[i], &info) == false)
    {
      continue;
    }

    if((info.vert.width * (float)i) + padding > rect.width - padding)
    {
      break;
    }

    if(skin->getButton()->getAlignment() == TextAnchor::MiddleLeft)
    {
      positions.push_back(Rect(rect.x + padding + info.vert.width * i,
                               rect.y + (rect.height / 2) - (info.vert.height / 2),
                               info.vert.width, info.vert.height));

      uvs.push_back(info.uv);

      //drawTextureWithTexCoords(Rect(rect.x + padding + info.vert.width * i,
      //                              rect.y + (rect.height / 2) - (info.vert.height / 2),
      //                              info.vert.width,
      //                              info.vert.height),
      //                              (Texture*)skin->getButton()->font->texture.get(), info.uv);

    }
    else
    {
      positions.push_back(Rect(rect.x + (rect.width / 2) - ((info.vert.width * text.length()) / 2) + info.vert.width * i,
                               rect.y + (rect.height / 2) - (info.vert.height / 2),
                               info.vert.width, info.vert.height));

      uvs.push_back(info.uv);

      //drawTextureWithTexCoords(Rect(rect.x + (rect.width / 2) - ((info.vert.width * text.length()) / 2) + info.vert.width * i,
      //                              rect.y + (rect.height / 2) - (info.vert.height / 2),
      //                              info.vert.width,
      //                              info.vert.height),
      //                              (Texture*)skin->getButton()->font->texture.get(), info.uv);
    }
  }

  if(positions.size() == uvs.size() && positions.size() > 0)
  {
    drawTextureWithTexCoords(positions, (Texture*)skin->getButton()->font->texture.get(), uvs);
  }
}

GuiSkin* Gui::getSkin()
{
  if(skin == NULL)
  {
    return GuiSkin::_default;
  }

  return skin;
}

bool Gui::button(Rect rect, Texture* image)
{
  bool result;
  Rect imgRect;

  result = button(rect, "");
  imgRect.width = image->getWidth();
  imgRect.height = image->getHeight();
  imgRect.x = rect.x + (rect.width / 2.0f) - (imgRect.width / 2.0f);
  imgRect.y = rect.y + (rect.height / 2.0f) - (imgRect.height / 2.0f);
  drawTexture(imgRect, image);

  return result;
}

bool Gui::button(Rect rect, std::string text)
{
  GuiSkin* skin = Gui::skin;

  if(skin == NULL)
  {
    skin = GuiSkin::_default;
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

void Gui::drawTextureWithTexCoords(std::vector<Rect> positions, Texture* texture, std::vector<Rect> texCoords)
{
  Material* guiMaterial = Material::guiMaterial;

  guiMaterial->setMatrix("in_Projection", Matrix4x4::ortho(0, Screen::getWidth(), Screen::getHeight(), 0, -1, 1));
  guiMaterial->setMatrix("in_View", Matrix4x4::getIdentity());
  guiMaterial->setMatrix("in_Model", getMatrix());
  Graphics::drawTextureBatch(positions, texture, texCoords, guiMaterial);
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
  Material* guiMaterial = Material::guiMaterial;

  guiMaterial->setMatrix("in_Projection", Matrix4x4::ortho(0, Screen::getWidth(), Screen::getHeight(), 0, -1, 1));
  guiMaterial->setMatrix("in_View", Matrix4x4::getIdentity());
  guiMaterial->setMatrix("in_Model", getMatrix());

  Graphics::drawTexture(rect, texture, Rect(0, 0, 1, 1),
                        style->border.left,
                        style->border.right,
                        style->border.top,
                        style->border.bottom,
                        guiMaterial);
}

void Gui::box(Rect rect, std::string text)
{
  GuiSkin* skin = Gui::skin;

  if(skin == NULL)
  {
    skin = GuiSkin::_default;
  }

  drawUi(rect, (Texture*)skin->getBox()->getNormal()->getBackground(), skin->getBox());
  label(rect, text);
}

}

}

