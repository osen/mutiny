#ifndef PROJECTSCREEN_H
#define PROJECTSCREEN_H

#include <mutiny/mutiny.h>

using namespace mutiny::engine;

class ProjectScreen : public Behaviour
{
public:
  virtual void onAwake();
  virtual void onGui();

private:
  Rect headerRect;
  Rect filesRect;
  Rect inspectorRect;
  Rect hierarchyRect;
  Rect logRect;

};

#endif

