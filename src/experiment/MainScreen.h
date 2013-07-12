#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include <mutiny/mutiny.h>

#include <memory>

using namespace mutiny::engine;

class MainScreen : public Behaviour
{
public:
  virtual void onAwake();
  virtual void onGui();

private:
  GameObject* cameraGo;
  GameObject* cubeGo;
  GameObject* centerGo;


};

#endif

