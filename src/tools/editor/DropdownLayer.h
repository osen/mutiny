#ifndef DROPDOWNLAYER_H
#define DROPDOWNLAYER_H

#include <mutiny/mutiny.h>

#include <string>
#include <memory>

using namespace mutiny::engine;

class ProjectScreen;

class DropdownLayer
{
public:
  bool enabled;
  Rect rect;
  Rect captionRect;
  std::string caption;
  bool released;
  std::string items;
  void (*callback)(std::string);

  std::shared_ptr<Texture2d> color;

  ProjectScreen* parent;

  DropdownLayer(ProjectScreen* parent);

  void onGui();

};

#endif
