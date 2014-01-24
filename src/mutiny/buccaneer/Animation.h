#ifndef MUTINY_ENGINE_ANIMATION_H
#define MUTINY_ENGINE_ANIMATION_H

#include "../Object.h"

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

};

class AnimationFrame
{
public:
  std::vector<AnimationTransform> transforms;

};

class Animation : public Object
{
  friend class mutiny::engine::Resources;
  friend class mutiny::engine::AnimatedMeshRenderer;
  friend class ::MainScreen;
  friend class ::Timeline;

public:
  int getFrameCount();
  void save(std::string path);

private:
  static Animation* load(std::string path);

  std::vector<AnimationFrame> frames;

};

}

}

#endif

