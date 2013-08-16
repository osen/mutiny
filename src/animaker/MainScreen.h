#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include <mutiny/mutiny.h>

#include <memory>

using namespace mutiny::engine;

class MainScreen : public Behaviour
{
public:
  virtual void onAwake();
  virtual void onUpdate();
  virtual void onGui();

private:
  AnimatedMesh* animatedMesh;
  GameObject* root;
  GameObject* animationGo;
  Vector2 lastMousePosition;
  Material* selectedMaterial;

  GameObject* selectedPart;
  std::vector<Material*> origMaterials;

  void selectPart(std::string partName);

};

#endif

