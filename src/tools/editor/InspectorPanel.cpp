#include "InspectorPanel.h"
#include "ProjectScreen.h"
#include "FilesPanel.h"
#include "Header.h"
#include "Util.h"

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

  if(previewTexture != NULL)
  {
    Gui::drawTexture(Rect(position.x, position.y, 128, 128), previewTexture);
  }
}

void InspectorPanel::onPathChanged(std::string newPath)
{
  std::string suffix;
  std::string path;

  for(int i = newPath.length() - 1; i >= 0; i--)
  {
    if(newPath[i] == '.')
    {
      suffix = newPath.substr(i + 1);
      break;
    }
  }

  if(suffix != "png")
  {
    return;
  }

  std::cout << "Suffix: " << suffix << std::endl;
  path = newPath.substr(0, newPath.length() - suffix.length() - 1);

  std::cout << "Loading: " << path << std::endl;
  previewTexture = Resources::load<Texture2d>(path);

  if(previewTexture == NULL)
  {
    std::cout << "Failed to load" << std::endl;
  }
}
