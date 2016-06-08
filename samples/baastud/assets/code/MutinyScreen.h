#ifndef MUTINYSCREEN_H
#define MUTINYSCREEN_H

#include <mutiny/mutiny.h>

using namespace mutiny::engine;

class MutinyScreen : public Behaviour
{
public:
  static ref<GameObject> create();

  virtual void onAwake();
  virtual void onGui();

private:
  ref<Texture2d> mutinyLogo;
  ref<Texture2d> background;
  float timeout;

};

#endif

