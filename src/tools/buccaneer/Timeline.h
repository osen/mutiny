#ifndef TIMELINE_H
#define TIMELINE_H

#include <mutiny/mutiny.h>

using namespace mutiny::engine;

class MainScreen;

class Timeline : public Behaviour
{
public:
  static Timeline* create(MainScreen* mainScreen);

  virtual void onAwake();
  virtual void onUpdate();
  virtual void onGui();

private:
  MainScreen* mainScreen;
  AnimatedMeshRenderer* amr;
  Texture2d* test;

};

#endif

