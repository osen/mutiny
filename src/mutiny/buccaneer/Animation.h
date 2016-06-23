#ifndef MUTINY_ENGINE_ANIMATION_H
#define MUTINY_ENGINE_ANIMATION_H

#include "../Object.h"
#include "../ref.h"

#include <string>
#include <vector>

class MainScreen;
class Timeline;

namespace mutiny
{

namespace engine
{

class Resources;
class AnimatedMeshRenderer;

class AnimationTransform : public enable_ref
{
public:
  std::string partName;
  float pX;
  float pY;
  float pZ;
  float rX;
  float rY;
  float rZ;

  AnimationTransform();
  static shared<AnimationTransform> copy(ref<AnimationTransform> other);

};

class AnimationFrame : public enable_ref
{
public:
  static shared<AnimationFrame> copy(ref<AnimationFrame> other);
  AnimationFrame();
  std::vector<shared<AnimationTransform> > transforms;

};

class Animation : public Object
{
  friend class mutiny::engine::Resources;
  friend class mutiny::engine::AnimatedMeshRenderer;
  friend class ::MainScreen;
  friend class ::Timeline;

public:
  Animation();
  int getFrameCount();
  void save(std::string path);
  std::vector<shared<AnimationFrame> > copyFrames();

private:
  static Animation* load(std::string path);

  std::vector<shared<AnimationFrame> > frames;

};

}

}

#endif

