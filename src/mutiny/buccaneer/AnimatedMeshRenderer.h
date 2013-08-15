#ifndef MUTINY_ENGINE_ANIMATEDMESHRENDERER_H
#define MUTINY_ENGINE_ANIMATEDMESHRENDERER_H

#include "../Behaviour.h"

namespace mutiny
{

namespace engine
{

class GameObject;
class AnimatedMesh;

class AnimatedMeshRenderer : public Behaviour
{
public:
  void setAnimatedMesh(AnimatedMesh* mesh);
  AnimatedMesh* getAnimatedMesh();

private:
  AnimatedMesh* mesh;
  GameObject* rootGo;

  virtual void onAwake();

};

}

}

#endif

