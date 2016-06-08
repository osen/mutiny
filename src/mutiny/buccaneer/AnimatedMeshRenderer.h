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
  void setAnimatedMesh(ref<AnimatedMesh> mesh);
  ref<AnimatedMesh> getAnimatedMesh();
  void setAnimation(ref<Animation> animation);
  ref<Animation> getAnimation();
  void play();
  void playOnce();
  void stop();
  bool isPlaying();
  float getFrame();
  void setFrame(float frame);
  void setFps(float fps);
  ref<GameObject> getRoot();
  void setInterpolateEnd(bool interpolateEnd);

private:
  std::vector<shared<Material> > materials;
  ref<AnimatedMesh> mesh;
  ref<Animation> animation;
  ref<GameObject> rootGo;
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

