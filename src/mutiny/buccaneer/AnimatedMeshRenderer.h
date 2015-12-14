#ifndef MUTINY_ENGINE_ANIMATEDMESHRENDERER_H
#define MUTINY_ENGINE_ANIMATEDMESHRENDERER_H

#include "../Behaviour.h"
#include "../arc.h"

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
  void setAnimatedMesh(arc<AnimatedMesh> mesh);
  arc<AnimatedMesh> getAnimatedMesh();
  void setAnimation(arc<Animation> animation);
  arc<Animation> getAnimation();
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
  std::vector<arc<Material> > materials;
  arc<AnimatedMesh> mesh;
  arc<Animation> animation;
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

