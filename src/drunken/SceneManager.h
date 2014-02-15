#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <mutiny/mutiny.h>

using namespace mutiny::engine;

class SceneManager : public Behaviour
{
public:
  virtual void onAwake();
  virtual void onLevelWasLoaded();

private:

  void loadLevel();

};

#endif

