#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include <mutiny/mutiny.h>

#include <memory>

using namespace mutiny::engine;

class SplashScreen : public Behaviour
{
public:
  virtual void onAwake();
  virtual void onGui();

private:
  shared<Texture2d> background;
  ref<Texture2d> splashLogo;
  float timeout;


};

#endif

