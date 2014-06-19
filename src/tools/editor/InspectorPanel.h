#ifndef INSPECTORPANEL_H
#define INSPECTORPANEL_H

#include "EditorWindow.h"

class ProjectScreen;

class InspectorPanel : public EditorWindow
{
public:
  ProjectScreen* parent;
  Texture2d* previewTexture;

  InspectorPanel(ProjectScreen* parent);

  void onGui();

  void onPathChanged(std::string newPath);

};

#endif

