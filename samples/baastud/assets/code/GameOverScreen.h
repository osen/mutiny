#ifndef GAMEOVERSCREEN_H
#define GAMEOVERSCREEN_H

#include <mutiny/mutiny.h>

using namespace mutiny::engine;

class QuickNumber;

class GameOverScreen : public Behaviour
{
public:
  static int score;

  static ref<GameObject> create();

  virtual void onAwake();
  virtual void onGui();

private:
  shared<QuickNumber> qn;
  ref<Texture2d> background;
  float timeout;

};

#endif

