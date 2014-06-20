#include "InspectorPanel.h"
#include "ProjectScreen.h"
#include "FilesPanel.h"
#include "Header.h"
#include "Util.h"
#include "InspectorCamera.h"

#include <string>

InspectorPanel::InspectorPanel(ProjectScreen* parent)
{
  setTitle("Inspector");
  this->parent = parent;
  previewTexture = NULL;
  headerTexture = Resources::load<Texture2d>("gui/header");

  previewBg.reset(new Texture2d(1, 1));
  previewBg->setPixel(0, 0, Color(0.171f, 0.171f, 0.171f, 1));
  previewBg->apply();
}

void InspectorPanel::onGui()
{
  position.width = 300;
  position.x = Screen::getWidth() - position.width;
  position.y = parent->header->position.height;
  position.height = Screen::getHeight() - parent->header->position.height;

  if(suffix == "png")
  {
    textureGui();
  }
  else if(suffix == "obj")
  {
    meshGui();
  }
  else if(suffix == "ogg")
  {
    audioClipGui();
  }
}

void InspectorPanel::textureGui()
{
  Rect previewRect(position.x, position.y + position.height -
    (position.width / 2), position.width, (position.width / 2));

  Gui::drawTexture(previewRect, previewBg.get());

  Gui::drawTexture(Rect(previewRect.x, previewRect.y - 20, previewRect.width,
    20), headerTexture);

  Gui::label(Rect(previewRect.x, previewRect.y - 20, previewRect.width,
    20), "Preview");

  if(previewTexture != NULL)
  {
    float xscale = 1.0f;
    float yscale = 1.0f;
    float scale = 1.0f;

    if(previewTexture->getWidth() > previewRect.width)
    {
      xscale = previewRect.width / previewTexture->getWidth();
    }

    if(previewTexture->getHeight() > previewRect.height)
    {
      yscale = previewRect.height / previewTexture->getHeight();
    }

    scale = xscale;

    if(yscale < scale)
    {
      scale = yscale;
    }

    Rect texRect(previewRect.x, previewRect.y,
      previewTexture->getWidth() * scale, previewTexture->getHeight() * scale);

    texRect.x = previewRect.x + previewRect.width / 2 - texRect.width / 2;
    texRect.y = previewRect.y + previewRect.height / 2 - texRect.height / 2;

    Gui::drawTexture(texRect,
      previewTexture);
  }
}

void InspectorPanel::audioClipGui()
{
  Gui::button(Rect(position.x + 20, position.y + 20, 75, 25), "Play");
}

void InspectorPanel::meshGui()
{
  Texture* rt = parent->inspectorCamera->getRenderTexture();
  Gui::button(Rect(position.x + 20, position.y + 20, 75, 25), "Edit");

  Rect previewRect(position.x, position.y + position.height -
    (position.width / 2), position.width, (position.width / 2));

  Gui::drawTexture(previewRect, previewBg.get());

  Gui::drawTexture(Rect(previewRect.x, previewRect.y - 20, previewRect.width,
    20), headerTexture);

  Gui::label(Rect(previewRect.x, previewRect.y - 20, previewRect.width,
    20), "Preview");

  if(rt != NULL)
  {
    float xscale = 1.0f;
    float yscale = 1.0f;
    float scale = 1.0f;

    if(Screen::getWidth() > previewRect.width)
    {
      xscale = previewRect.width / Screen::getWidth();
    }

    if(Screen::getHeight() > previewRect.height)
    {
      yscale = previewRect.height / Screen::getHeight();
    }

    scale = xscale;

    if(yscale < scale)
    {
      scale = yscale;
    }

    Rect texRect(previewRect.x, previewRect.y,
      Screen::getWidth() * scale, Screen::getHeight() * scale);

    texRect.x = previewRect.x + previewRect.width / 2 - texRect.width / 2;
    texRect.y = previewRect.y + previewRect.height / 2 - texRect.height / 2;


    GuiUtility::rotateAroundPivot(180, Vector2(texRect.x + texRect.width / 2,
      texRect.y + texRect.height / 2));

    Gui::drawTexture(texRect, rt);

    GuiUtility::rotateAroundPivot(-180, Vector2(texRect.x + texRect.width / 2,
      texRect.y + texRect.height / 2));
  }
}

void InspectorPanel::onPathChanged(std::string newPath)
{
  for(int i = newPath.length() - 1; i >= 0; i--)
  {
    if(newPath[i] == '.')
    {
      suffix = newPath.substr(i + 1);
      break;
    }
  }

  path = newPath.substr(0, newPath.length() - suffix.length() - 1);

  if(suffix == "png")
  {
    previewTexture = Resources::load<Texture2d>(path);

    if(previewTexture == NULL)
    {
      std::cout << "Failed to load" << std::endl;
    }
  }
  else if(suffix == "obj")
  {
    Mesh* previewMesh = Resources::load<Mesh>(path);

    if(previewMesh == NULL)
    {
      std::cout << "Failed to load" << std::endl;
    }

    parent->inspectorMf->setMesh(previewMesh);
  }
  else if(suffix == "ogg")
  {

  }
}
