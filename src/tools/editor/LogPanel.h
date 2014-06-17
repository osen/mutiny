#ifndef LOGPANEL_H
#define LOGPANEL_H

#include "EditorWindow.h"

#include <memory>

class ProjectScreen;

class LogPanel : public EditorWindow
{
public:
  ProjectScreen* parent;

  LogPanel(ProjectScreen* parent);

  void onGui();

};

#endif

