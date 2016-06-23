#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include <mutiny/mutiny.h>

#include <memory>

using namespace mutiny::engine;

class Timeline;

class MainScreen : public Behaviour
{
  friend class Timeline;

public:
  virtual void onAwake();
  virtual void onUpdate();
  virtual void onGui();

private:
  ref<AnimatedMesh> animatedMesh;
  ref<AnimatedMeshRenderer> amr;
  std::string animationPath;
  ref<Animation> animation;
  ref<GameObject> root;
  ref<GameObject> animationGo;
  Vector2 lastMousePosition;
  ref<Material> selectedMaterial;
  float pulseAmount;
  bool pulseDown;
  shared<Texture2d> fallbackTex;
  bool changeMade;
  int transformMode;
  ref<Timeline> timeline;

  ref<GameObject> selectedPart;
  std::vector<ref<Material> > origMaterials;
  std::vector<shared<Material> > newMaterials;
  std::vector<std::vector<shared<AnimationFrame> > > undoBuffer;

  void modifyTransform(ref<AnimationTransform> transform);
  void selectPart(std::string partName);

};

#endif

