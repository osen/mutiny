#include "SelectProjectScreen.h"
#include "EditorGuiUtil.h"

#include <sys/types.h>
#include <dirent.h>

#define PADDING 10

void SelectProjectScreen::onAwake()
{
  DIR* dp = NULL;
  struct dirent* ep = NULL;

  Screen::setResolution(580, 350, false);
  Gui::getSkin()->getButton()->setAlignment(TextAnchor::MiddleLeft);
  displayOpenGui = true;
  currentTab = "Open Project";

  dp = opendir(std::string(Application::getDataPath() + "/..").c_str());

  if(dp != NULL)
  {
    while(ep = readdir(dp))
    {
      std::string filename = ep->d_name;

      if(filename == "." || filename == ".." || filename == "editor" || filename == "mutiny" || filename == "buccaneer")
      {
        continue;
      }

      projects.push_back(filename);
    }

    closedir (dp);
  }

  if(projects.size() > 0)
  {
    selectedProject = projects.at(0);
  }
}

void SelectProjectScreen::onGui()
{
  std::vector<std::string> tabs;
  centerPanel.width = 550;
  centerPanel.height = 300;

  tabs.push_back("Open Project");
  tabs.push_back("New Project");

  centerPanel.x = (Screen::getWidth() / 2) - (centerPanel.width / 2);
  centerPanel.y = 10 + (Screen::getHeight() / 2) - (centerPanel.height / 2);

  Gui::box(centerPanel, "");
  currentTab = EditorGuiUtil::tabs(Rect(centerPanel.x, centerPanel.y - 20, 100, 20), &tabs, currentTab);

  if(currentTab == "Open Project")
  {
    openProjectGui();
  }
  else
  {
    createProjectGui();
  }
}

void SelectProjectScreen::openProjectGui()
{
  Gui::label(Rect(centerPanel.x + PADDING,
                  centerPanel.y + PADDING, 300, 30),
                  "Select project to open:");

  if(Gui::button(Rect(centerPanel.x + centerPanel.width - 100 - PADDING,
                      centerPanel.y + centerPanel.height - 25 - PADDING,
                      100, 25), "Open") == true)
  {
    openButtonClicked();
  }

  int yPad = 50;
  Rect selectRect(centerPanel.x + PADDING, centerPanel.y + yPad, centerPanel.width - (PADDING * 2), centerPanel.height - (yPad * 2));
  Gui::box(selectRect, "");

  for(int i = 0; i < projects.size(); i++)
  {
    Rect itemRect(selectRect.x, selectRect.y + (20 * i), selectRect.width, 20);
    if(projects.at(i) == selectedProject)
    {
      Gui::box(itemRect, projects.at(i));
    }
    else
    {
      Gui::label(itemRect, projects.at(i));
    }

    if(Input::getMouseButtonDown(0) == true && itemRect.contains(Input::getMousePosition()) == true)
    {
      selectedProject = projects.at(i);
    }
  }
}

void SelectProjectScreen::createProjectGui()
{
  Gui::label(Rect(centerPanel.x + PADDING,
                  centerPanel.y + PADDING, 300, 30),
                  "Project Location:");

  if(Gui::button(Rect(centerPanel.x + centerPanel.width - 100 - PADDING,
                      centerPanel.y + centerPanel.height - 25 - PADDING,
                      100, 25), "Create") == true)
  {
    createButtonClicked();
  }
}

void SelectProjectScreen::createButtonClicked()
{

}

void SelectProjectScreen::openButtonClicked()
{
  Application::loadLevel("Project");
}

