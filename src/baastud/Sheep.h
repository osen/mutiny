#ifndef SHEEP_H
#define SHEEP_H

#include <mutiny/mutiny.h>

using namespace mutiny::engine;

class Sheep : public Behaviour
{
public:
  static GameObject* create();

  virtual void onUpdate();

private:

};

#endif

