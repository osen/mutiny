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
  if(previewTexture != NULL)
  {
    Gui::drawTexture(Rect(position.x, position.y, 128, 128), previewTexture);
  }
}

void InspectorPanel::audioClipGui()
{
  Gui::button(Rect(position.x + 20, position.y + 20, 75, 25), "Play");
}

void InspectorPanel::meshGui()
{
  Gui::button(Rect(position.x + 20, position.y + 20, 75, 25), "Edit");

  Gui::drawTexture(Rect(position.x, position.y, 128, 128),
    parent->inspectorCamera->getRenderTexture());
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

  }
  else if(suffix == "ogg")
  {

  }
}
