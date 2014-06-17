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
class LogPanel;

class ProjectScreen : public Behaviour
{
public:
  std::shared_ptr<Header> header;
  std::shared_ptr<FilesPanel> filesPanel;
  std::shared_ptr<HierarchyPanel> hierarchyPanel;
  std::shared_ptr<InspectorPanel> inspectorPanel;
  std::shared_ptr<ScenePanel> scenePanel;
  std::shared_ptr<LogPanel> logPanel;

  virtual void onAwake();
  virtual void onGui();

};

#endif

