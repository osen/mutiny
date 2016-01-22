#ifndef MUTINY_ENGINE_BEHAVIOUR_H
#define MUTINY_ENGINE_BEHAVIOUR_H

#include "Component.h"

namespace mutiny
{

namespace engine
{

class Behaviour : public Component
{
  friend class GameObject;

public:
  virtual ~Behaviour();

  virtual void onAwake();
  virtual void onStart();
  virtual void onUpdate();
  virtual void onPostRender();
  virtual void onGui();
  virtual void onDestroy();
  virtual void onLevelWasLoaded();

private:
  bool started;

  void awake();
  void update();
  void postRender();
  void gui();
  void destroy();
  void levelWasLoaded();

};

}

}

#endif

