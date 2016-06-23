#include "Animation.h"

#include "../Application.h"
#include "../Exception.h"
#include "../internal/Util.h"

#include <fstream>
#include <memory>
#include <cstdlib>

namespace mutiny
{

namespace engine
{

AnimationTransform::AnimationTransform()
{
  pX = 0;
  pY = 0;
  pZ = 0;
  rX = 0;
  rY = 0;
  rZ = 0;
}

int Animation::getFrameCount()
{
  return frames.size();
}

shared<AnimationTransform> AnimationTransform::copy(ref<AnimationTransform> other)
{
  shared<AnimationTransform> rtn(new AnimationTransform());

  rtn->partName = other->partName;
  rtn->pX = other->pX;
  rtn->pY = other->pY;
  rtn->pZ = other->pZ;
  rtn->rX = other->rX;
  rtn->rY = other->rY;
  rtn->rZ = other->rZ;

  return rtn;
}

shared<AnimationFrame> AnimationFrame::copy(ref<AnimationFrame> other)
{
  shared<AnimationFrame> rtn(new AnimationFrame());

  for(size_t i = 0; i < other->transforms.size(); i++)
  {
    rtn->transforms.push_back(AnimationTransform::copy(other->transforms.at(i)));
  }

  return rtn;
}

AnimationFrame::AnimationFrame()
{

}

Animation::Animation()
{

}

Animation* Animation::load(std::string path)
{
  std::string line;
  std::ifstream file;
  std::vector<std::string> splitLine;

  Animation* animation = new Animation();

  file.open(path.c_str());

  if(file.is_open() == false)
  {
    return NULL;
  }

  while(file.eof() == false)
  {
    getline(file, line);
    splitLine.clear();
    internal::Util::splitStringWhitespace(line, splitLine);

    if(splitLine.size() < 1)
    {
      continue;
    }

    if(splitLine.at(0) == "f")
    {
      animation->frames.push_back(shared<AnimationFrame>(new AnimationFrame()));
    }
    else if(splitLine.at(0) == "t")
    {
      shared<AnimationTransform> transform(new AnimationTransform());
      transform->partName = splitLine.at(1);
      transform->pX = atof(splitLine.at(2).c_str());
      transform->pY = atof(splitLine.at(3).c_str());
      transform->pZ = atof(splitLine.at(4).c_str());
      transform->rX = atof(splitLine.at(5).c_str());
      transform->rY = atof(splitLine.at(6).c_str());
      transform->rZ = atof(splitLine.at(7).c_str());
      animation->frames.at(animation->frames.size() - 1)->transforms.push_back(transform);
    }
  }

  return animation;
}

void Animation::save(std::string path)
{
  std::ofstream file;
  ref<AnimationFrame> frame;
  shared<AnimationTransform> transform;

  file.open(path.c_str());

  if(file.is_open() == false)
  {
    throw Exception("Failed to open file for writing");
  }

  for(int i = 0; i < frames.size(); i++)
  {
    file << "f" << std::endl;
    frame = frames.at(i);

    for(int j = 0; j < frame->transforms.size(); j++)
    {
      transform = frame->transforms.at(j);

      file << "t "
           << transform->partName << " "
           << transform->pX << " "
           << transform->pY << " "
           << transform->pZ << " "
           << transform->rX << " "
           << transform->rY << " "
           << transform->rZ << std::endl;
    }
  }
}

}

}

