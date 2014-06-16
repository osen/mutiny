#ifndef SELECTPROJECTSCREEN_H
#define SELECTPROJECTSCREEN_H

#include <mutiny/mutiny.h>

#include <vector>
#include <string>

using namespace mutiny::engine;

class SelectProjectScreen : public Behaviour
{
public:
  virtual void onAwake();
  virtual void onGui();

private:
  Rect centerPanel;
  bool displayOpenGui;
  std::string currentTab;
  std::vector<std::string> projects;
  std::string selectedProject;

  void openProjectGui();
  void createProjectGui();

  void createButtonClicked();
  void openButtonClicked();

};

#endif

