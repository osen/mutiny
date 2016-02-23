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
  Texture2d* background;
  Texture2d* splashLogo;
  float timeout;


};

#endif

