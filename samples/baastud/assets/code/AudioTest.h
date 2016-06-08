#ifndef AUDIOTEST_H
#define AUDIOTEST_H

#include <mutiny/mutiny.h>

class Audio;

using namespace mutiny::engine;

class AudioTest : public Behaviour
{
public:
  static ref<GameObject> create();

  virtual void onAwake();
  virtual void onGui();

private:
  shared<Audio> audio;
};

#endif
