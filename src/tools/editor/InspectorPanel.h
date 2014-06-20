#ifndef INSPECTORPANEL_H
#define INSPECTORPANEL_H

#include "EditorWindow.h"

#include <memory>

class ProjectScreen;

class InspectorPanel : public EditorWindow
{
public:
  ProjectScreen* parent;
  std::string suffix;
  std::string path;

  Texture2d* previewTexture;
  Texture2d* headerTexture;
  std::shared_ptr<Texture2d> previewBg;

  InspectorPanel(ProjectScreen* parent);

  void onGui();

  void onPathChanged(std::string newPath);

  void textureGui();
  void audioClipGui();
  void meshGui();

};

#endif

