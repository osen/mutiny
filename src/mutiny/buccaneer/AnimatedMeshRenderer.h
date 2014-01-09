#ifndef MUTINY_ENGINE_ANIMATEDMESHRENDERER_H
#define MUTINY_ENGINE_ANIMATEDMESHRENDERER_H

#include "../Behaviour.h"

#include <vector>
#include <memory>

namespace mutiny
{

namespace engine
{

class GameObject;
class AnimatedMesh;
class Material;
class Animation;

class AnimatedMeshRenderer : public Behaviour
{
public:
  void setAnimatedMesh(AnimatedMesh* mesh);
  AnimatedMesh* getAnimatedMesh();
  void setAnimation(Animation* animation);
  Animation* getAnimation();

private:
  std::vector<std::unique_ptr<Material> > materials;
  AnimatedMesh* mesh;
  Animation* animation;
  GameObject* rootGo;
  float frame;

  virtual void onAwake();
  virtual void onUpdate();

};

}

}

#endif

