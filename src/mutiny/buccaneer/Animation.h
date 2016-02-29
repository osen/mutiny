#ifndef MUTINY_ENGINE_ANIMATION_H
#define MUTINY_ENGINE_ANIMATION_H

#include "../Object.h"
#include "../internal/gcmm.h"

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

class AnimationTransform
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
  static AnimationTransform* copy(AnimationTransform* other);

};

class AnimationFrame
{
public:
  static AnimationFrame* copy(AnimationFrame* other);
  AnimationFrame();
  internal::gc::list<AnimationTransform*>* transforms;

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

private:
  static Animation* load(std::string path);

  internal::gc::list<AnimationFrame*>* frames;

};

}

}

#endif

