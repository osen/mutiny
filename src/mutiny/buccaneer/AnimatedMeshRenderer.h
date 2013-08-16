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

class AnimatedMeshRenderer : public Behaviour
{
public:
  void setAnimatedMesh(AnimatedMesh* mesh);
  AnimatedMesh* getAnimatedMesh();

private:
  std::vector<std::unique_ptr<Material> > materials;
  AnimatedMesh* mesh;
  GameObject* rootGo;

  virtual void onAwake();

};

}

}

#endif

