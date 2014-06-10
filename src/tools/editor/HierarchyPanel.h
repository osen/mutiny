#ifndef HIERARCHYPANEL_H
#define HIERARCHYPANEL_H

#include <mutiny/mutiny.h>

using namespace mutiny::engine;

class ProjectScreen;

class HierarchyPanel
{
public:
  Rect rect;
  ProjectScreen* parent;

  HierarchyPanel(ProjectScreen* parent);

  void onGui();

};

#endif

