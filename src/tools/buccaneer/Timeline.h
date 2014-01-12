#ifndef TIMELINE_H
#define TIMELINE_H

#include <mutiny/mutiny.h>

using namespace mutiny::engine;

class Timeline : public Behaviour
{
public:
  static Timeline* create(AnimatedMeshRenderer* amr);

  virtual void onAwake();
  virtual void onUpdate();
  virtual void onGui();

private:
  AnimatedMeshRenderer* amr;
  Texture2d* test;

};

#endif

