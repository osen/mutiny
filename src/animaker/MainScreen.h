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
  float pulseAmount;
  bool pulseDown;

  GameObject* selectedPart;
  std::vector<Material*> origMaterials;
  std::vector<std::unique_ptr<Material> > newMaterials;

  void selectPart(std::string partName);

};

#endif

