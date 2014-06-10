#ifndef HEADER_H
#define HEADER_H

#include <mutiny/mutiny.h>

using namespace mutiny::engine;

class ProjectScreen;

class Header
{
public:
  Rect rect;

  Header(ProjectScreen* parent);

  void onGui();

};

#endif

