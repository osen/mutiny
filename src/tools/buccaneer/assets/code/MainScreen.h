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
  AnimatedMesh* animatedMesh;
  AnimatedMeshRenderer* amr;
  std::string animationPath;
  Animation* animation;
  GameObject* root;
  GameObject* animationGo;
  Vector2 lastMousePosition;
  Material* selectedMaterial;
  float pulseAmount;
  bool pulseDown;
  Texture2d* fallbackTex;
  bool changeMade;
  int transformMode;
  Timeline* timeline;

  GameObject* selectedPart;
  gclist<Material*>* origMaterials;
  gclist<Material*>* newMaterials;
  gclist<gclist<AnimationFrame*>*>* undoBuffer;

  void modifyTransform(AnimationTransform* transform);
  void selectPart(std::string partName);

};

#endif

