#ifndef SELECTPROJECTSCREEN_H
#define SELECTPROJECTSCREEN_H

#include <mutiny/mutiny.h>

using namespace mutiny::engine;

class SelectProjectScreen : public Behaviour
{
public:
  virtual void onAwake();
  virtual void onGui();

private:
  Rect centerPanel;
  bool displayOpenGui;

  void openProjectGui();
  void createProjectGui();

  void createButtonClicked();
  void openButtonClicked();

};

#endif

