#ifndef HIERARCHYPANEL_H
#define HIERARCHYPANEL_H

#include "EditorWindow.h"

#include <memory>

class ProjectScreen;

class HierarchyPanel : public EditorWindow
{
public:
  ProjectScreen* parent;

  Texture2d* expandTexture;
  Texture2d* scrollbarTexture;
  std::shared_ptr<Texture2d> selectedTexture;

  int startDisplay;
  int maxDisplay;
  int totalDisplay;

  bool scrolling;
  float scrollPos;
  float mousePos;
  GameObject* selectedGo;

  HierarchyPanel(ProjectScreen* parent);

  void onGui();

  void header();
  void listGameObjects();
  void listGameObjects(int* indent, int* y, int* total, GameObject* gameObject);
  void displayScrollbars();

};

#endif

