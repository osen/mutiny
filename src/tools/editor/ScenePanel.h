#ifndef SCENEPANEL_H
#define SCENEPANEL_H

#include "EditorWindow.h"

class ProjectScreen;

class ScenePanel : public EditorWindow
{
public:
  ProjectScreen* parent;

  ScenePanel(ProjectScreen* parent);

  void onGui();

};

#endif

