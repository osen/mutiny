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
  virtual void onGui();
  virtual void onDestroy();
  virtual void onLevelWasLoaded();

private:
  bool started;

  virtual void awake();
  virtual void update();
  virtual void gui();
  virtual void destroy();
  virtual void levelWasLoaded();

};

}

}

#endif

