#ifndef TIMELINE_H
#define TIMELINE_H

#include <mutiny/mutiny.h>

using namespace mutiny::engine;

class MainScreen;

class Timeline : public Behaviour
{
public:
  static ref<Timeline> create(ref<MainScreen> mainScreen);

  virtual void onAwake();
  virtual void onUpdate();
  virtual void onGui();

private:
  ref<MainScreen> mainScreen;
  ref<AnimatedMeshRenderer> amr;
  ref<Texture2d> test;
  ref<Texture2d> whitePixel;
  ref<Texture2d> cursor;

};

#endif

