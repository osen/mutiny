#include "SelectProjectScreen.h"

#define PADDING 10

void SelectProjectScreen::onAwake()
{
  Gui::getSkin()->getButton()->setAlignment(TextAnchor::MiddleLeft);
  displayOpenGui = true;
}

void SelectProjectScreen::onGui()
{
  centerPanel.width = 500;
  centerPanel.height = 300;

  centerPanel.x = (Screen::getWidth() / 2) - (centerPanel.width / 2);
  centerPanel.y = (Screen::getHeight() / 2) - (centerPanel.height / 2);

  Gui::box(centerPanel, "");

  if(displayOpenGui == true)
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
  if(Gui::button(Rect(centerPanel.x + PADDING,
                      centerPanel.y + PADDING, 225, 30),
                      "Create New Project") == true)
  {
    displayOpenGui = !displayOpenGui;
  }

  Gui::label(Rect(centerPanel.x + PADDING,
                  centerPanel.y + PADDING + 30 + PADDING, 300, 30),
                  "Select project to open:");

  if(Gui::button(Rect(centerPanel.x + centerPanel.width - 100 - PADDING,
                      centerPanel.y + centerPanel.height - 25 - PADDING,
                      100, 25), "Open") == true)
  {
    openButtonClicked();
  }
}

void SelectProjectScreen::createProjectGui()
{
  if(Gui::button(Rect(centerPanel.x + PADDING,
                      centerPanel.y + PADDING, 225, 30),
                      "Open Project") == true)
  {
    displayOpenGui = !displayOpenGui;
  }

  Gui::label(Rect(centerPanel.x + PADDING,
                  centerPanel.y + PADDING + 30 + PADDING, 300, 30),
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

