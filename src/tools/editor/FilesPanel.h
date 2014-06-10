#ifndef FILESPANEL_H
#define FILESPANEL_H

#include <mutiny/mutiny.h>

using namespace mutiny::engine;

class ProjectScreen;

class FilesPanel
{
public:
  Rect rect;
  ProjectScreen* parent;

  FilesPanel(ProjectScreen* parent);

  void onGui();

};

#endif

