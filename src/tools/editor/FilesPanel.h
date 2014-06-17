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
  Texture2d* scrollbarTexture;
  std::shared_ptr<Texture2d> selectedTexture;
  std::string selectedPath;
  int startDisplay;
  int maxDisplay;
  int totalDisplay;

  bool scrolling;
  float scrollPos;
  float mousePos;

  FilesPanel(ProjectScreen* parent);

  void onGui();
  void listFiles();
  void listFiles(int* indent, int* y, int* total, FileTree* item);
  void displayScrollbars();

};

#endif

