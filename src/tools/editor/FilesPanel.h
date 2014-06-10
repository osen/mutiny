#ifndef FILESPANEL_H
#define FILESPANEL_H

#include "EditorWindow.h"

class ProjectScreen;

class FilesPanel : public EditorWindow
{
public:
  ProjectScreen* parent;

  FilesPanel(ProjectScreen* parent);

  void onGui();

};

#endif

