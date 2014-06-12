#ifndef PROJECTSCREEN_H
#define PROJECTSCREEN_H

#include <mutiny/mutiny.h>

#include <memory>

using namespace mutiny::engine;

class Header;
class FilesPanel;
class HierarchyPanel;
class InspectorPanel;
class ScenePanel;

class ProjectScreen : public Behaviour
{
public:
  std::shared_ptr<Header> header;
  std::shared_ptr<FilesPanel> filesPanel;
  std::shared_ptr<HierarchyPanel> hierarchyPanel;
  std::shared_ptr<InspectorPanel> inspectorPanel;
  std::shared_ptr<ScenePanel> scenePanel;

  virtual void onAwake();
  virtual void onGui();

  Rect logRect;

};

#endif

