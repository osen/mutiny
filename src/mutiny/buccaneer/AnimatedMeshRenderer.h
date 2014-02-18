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
  void play();
  void playOnce();
  void stop();
  bool isPlaying();
  float getFrame();
  void setFrame(float frame);
  void setFps(float fps);
  GameObject* getRoot();
  void setInterpolateEnd(bool interpolateEnd);

private:
  std::vector<std::unique_ptr<Material> > materials;
  AnimatedMesh* mesh;
  Animation* animation;
  GameObject* rootGo;
  float frame;
  bool playing;
  bool once;
  float fps;
  bool interpolateEnd;

  virtual void onAwake();
  virtual void onUpdate();
  virtual void onDestroy();

};

}

}

#endif

