#ifndef LAYERSCREEN_H
#define LAYERSCREEN_H

#include <mutiny/mutiny.h>

using namespace mutiny::engine;

class LayerScreen : public Behaviour
{
public:
  static GameObject* create();

  virtual void onAwake();
  virtual void onUpdate();
  virtual void onGui();

private:
  GameObject* playerGo;
  GameObject* cameraGo;


};

#endif

