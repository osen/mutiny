#ifndef HEADER_H
#define HEADER_H

#include "EditorWindow.h"

#include <string>

class ProjectScreen;

class Header : public EditorWindow
{
public:
  Header(ProjectScreen* parent);

  void onGui();

private:
  Texture2d* playTexture;
  Texture2d* buildTexture;

  static void dropdownClicked(std::string item);

};

#endif

