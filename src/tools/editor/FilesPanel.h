#ifndef FILESPANEL_H
#define FILESPANEL_H

#include "EditorWindow.h"

class ProjectScreen;
class FileTree;

class FilesPanel : public EditorWindow
{
public:
  ProjectScreen* parent;
  std::shared_ptr<FileTree> files;
  Texture2d* expandTexture;

  FilesPanel(ProjectScreen* parent);

  void onGui();
  void listFiles();
  void listFiles(int* indent, int* y, FileTree* item);

};

#endif

