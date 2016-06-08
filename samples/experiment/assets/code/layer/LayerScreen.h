#ifndef LAYERSCREEN_H
#define LAYERSCREEN_H

#include <mutiny/mutiny.h>

using namespace mutiny::engine;

class LayerScreen : public Behaviour
{
public:
  static ref<GameObject> create();

  virtual void onAwake();
  virtual void onUpdate();
  virtual void onGui();

private:
  ref<GameObject> playerGo;
  ref<GameObject> cameraGo;


};

#endif

