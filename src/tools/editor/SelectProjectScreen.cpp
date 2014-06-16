#include "SelectProjectScreen.h"
#include "EditorGuiUtil.h"

#define PADDING 10

void SelectProjectScreen::onAwake()
{
  Screen::setResolution(600, 375, false);
  Gui::getSkin()->getButton()->setAlignment(TextAnchor::MiddleLeft);
  displayOpenGui = true;
  currentTab = "Open Project";
}

void SelectProjectScreen::onGui()
{
  std::vector<std::string> tabs;
  centerPanel.width = 550;
  centerPanel.height = 300;

  tabs.push_back("Open Project");
  tabs.push_back("New Project");

  centerPanel.x = (Screen::getWidth() / 2) - (centerPanel.width / 2);
  centerPanel.y = 15 + (Screen::getHeight() / 2) - (centerPanel.height / 2);

  Gui::box(centerPanel, "");
  currentTab = EditorGuiUtil::tabs(Rect(centerPanel.x, centerPanel.y - 30, 100, 30), &tabs, currentTab);

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

