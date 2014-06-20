#ifndef FLOOR_H
#define FLOOR_H

#include <mutiny/mutiny.h>

#include <memory>

using namespace mutiny::engine;

class Floor : public Behaviour
{
public:
  static Floor* create();

  virtual void onAwake();

private:
  std::shared_ptr<Mesh> mesh;
  std::shared_ptr<Material> material;

};

#endif
