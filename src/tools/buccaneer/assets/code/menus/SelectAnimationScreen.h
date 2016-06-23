#ifndef SELECTANIMATIONSCREEN_H
#define SELECTANIMATIONSCREEN_H

#include <mutiny/mutiny.h>

#include <string>
#include <vector>

using namespace mutiny::engine;

class SelectAnimationScreen : public Behaviour
{
public:
  static std::string choice;

  virtual void onAwake();
  virtual void onUpdate();
  virtual void onGui();
  virtual void onDestroy();

private:
  std::vector<std::string> files;
  ref<GameObject> modelGo;

};

#endif

