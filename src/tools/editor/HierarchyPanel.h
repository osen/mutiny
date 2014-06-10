#ifndef HIERARCHYPANEL_H
#define HIERARCHYPANEL_H

#include "EditorWindow.h"

class ProjectScreen;

class HierarchyPanel : public EditorWindow
{
public:
  ProjectScreen* parent;

  HierarchyPanel(ProjectScreen* parent);

  void onGui();

};

#endif

