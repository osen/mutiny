#ifndef INSPECTORPANEL_H
#define INSPECTORPANEL_H

#include "EditorWindow.h"

class ProjectScreen;

class InspectorPanel : public EditorWindow
{
public:
  ProjectScreen* parent;

  InspectorPanel(ProjectScreen* parent);

  void onGui();

};

#endif

