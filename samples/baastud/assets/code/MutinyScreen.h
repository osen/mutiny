#ifndef MUTINYSCREEN_H
#define MUTINYSCREEN_H

#include <mutiny/mutiny.h>

using namespace mutiny::engine;

class MutinyScreen : public Behaviour
{
public:
  static GameObject* create();

  virtual void onAwake();
  virtual void onGui();

private:
  Texture2d* mutinyLogo;
  Texture2d* background;
  float timeout;

};

#endif

