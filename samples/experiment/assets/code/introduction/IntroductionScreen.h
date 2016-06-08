#ifndef INTRODUCTIONSCREEN_H
#define INTRODUCTIONSCREEN_H

#include <mutiny/mutiny.h>

#include <memory>

using namespace mutiny::engine;

class IntroductionScreen : public Behaviour
{
public:
  static ref<GameObject> create();

  virtual void onAwake();
  virtual void onGui();

private:
  ref<GameObject> cameraGo;


};

#endif

