#ifndef INTRODUCTIONSCREEN_H
#define INTRODUCTIONSCREEN_H

#include <mutiny/mutiny.h>

#include <memory>

using namespace mutiny::engine;

class IntroductionScreen : public Behaviour
{
public:
  static GameObject* create();

  virtual void onAwake();
  virtual void onGui();

private:
  GameObject* cameraGo;


};

#endif

