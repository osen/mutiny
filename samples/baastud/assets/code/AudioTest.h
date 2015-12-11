#ifndef AUDIOTEST_H
#define AUDIOTEST_H

#include <mutiny/mutiny.h>

class Audio;

using namespace mutiny::engine;

class AudioTest : public Behaviour
{
public:
  static GameObject* create();

  virtual void onAwake();
  virtual void onGui();

private:
  arc<Audio> audio;
};

#endif
