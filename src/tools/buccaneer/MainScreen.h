#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include <mutiny/mutiny.h>

#include <memory>

using namespace mutiny::engine;

class Timeline;

class MainScreen : public Behaviour
{
public:
  virtual void onAwake();
  virtual void onUpdate();
  virtual void onGui();

private:
  AnimatedMesh* animatedMesh;
  AnimatedMeshRenderer* amr;
  Animation* animation;
  GameObject* root;
  GameObject* animationGo;
  Vector2 lastMousePosition;
  Material* selectedMaterial;
  float pulseAmount;
  bool pulseDown;
  std::unique_ptr<Texture2d> fallbackTex;
  bool changeMade;
  Timeline* timeline;

  GameObject* selectedPart;
  std::vector<Material*> origMaterials;
  std::vector<std::unique_ptr<Material> > newMaterials;
  std::vector<std::vector<AnimationFrame> > undoBuffer;

  void modifyTransform(AnimationTransform* transform);
  void selectPart(std::string partName);

};

#endif

