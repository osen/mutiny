#include "EditorWindow.h"
#include "EditorGuiUtil.h"

#include <vector>

EditorWindow::EditorWindow()
{
  headerTexture.reset(new Texture2d(1, 1));
  headerTexture->setPixel(0, 0, Color(0.171f, 0.171f, 0.171f, 1));
  headerTexture->apply();
}

EditorWindow::~EditorWindow() {}

void EditorWindow::gui()
{
  int headerHeight = 20;

  if(Input::getMouseButtonDown(0) == true &&
     position.contains(Input::getMousePosition()) == true)
  {
    // TODO: Unselect GUI elements.
  }

  if(title == "Header")
  {
    Gui::box(Rect(position.x, position.y, position.width, position.height + headerHeight + 1), "");
    Gui::drawTexture(Rect(position.x, position.y, position.width, position.height + headerHeight), headerTexture.get());
    onGui();
  }
  else if(title == "Scene")
  {
    onGui();
    Gui::drawTexture(Rect(position.x, position.y, position.width, headerHeight), headerTexture.get());
    Gui::label(Rect(position.x, position.y, 200, headerHeight), title);
  }
  else
  {
    Gui::box(Rect(position.x, position.y + headerHeight, position.width, position.height - headerHeight), "");
    onGui();
    Gui::drawTexture(Rect(position.x, position.y, position.width, headerHeight), headerTexture.get());
    Gui::label(Rect(position.x, position.y, 200, headerHeight), title);
  }

  if(title != "Header")
  {
    std::vector<std::string> tabNames;
    tabNames.push_back(title);

    EditorGuiUtil::tabs(Rect(position.x, position.y, 85, headerHeight),
      &tabNames, title);
  }
}

void EditorWindow::onGui()
{

}

void EditorWindow::setTitle(std::string title)
{
  this->title = title;
}
