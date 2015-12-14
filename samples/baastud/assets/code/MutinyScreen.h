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
  arc<Texture2d> mutinyLogo;
  arc<Texture2d> background;
  float timeout;

};

#endif

