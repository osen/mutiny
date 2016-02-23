#include "Animation.h"

#include "../Application.h"
#include "../Exception.h"
#include "../internal/Util.h"

#include <fstream>
#include <memory>

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
  return frames->size();
}

AnimationFrame::AnimationFrame()
{
  transforms = Application::getGC()->gc_list<AnimationTransform*>();
}

Animation::Animation()
{
  frames = Application::getGC()->gc_list<AnimationFrame*>();
}

Animation* Animation::load(std::string path)
{
  std::string line;
  std::ifstream file;
  std::vector<std::string> splitLine;

  Animation* animation = Application::getGC()->gc_new<Animation>();

  file.open(path.c_str());

  if(file.is_open() == false)
  {
    return NULL;
  }

  while(file.eof() == false)
  {
    getline(file, line);
    splitLine.clear();
    internal::Util::splitStringWhitespace(line, &splitLine);

    if(splitLine.size() < 1)
    {
      continue;
    }

    if(splitLine.at(0) == "f")
    {
      animation->frames->push_back(Application::getGC()->gc_new<AnimationFrame>());
    }
    else if(splitLine.at(0) == "t")
    {
      AnimationTransform* transform = Application::getGC()->gc_new<AnimationTransform>();
      transform->partName = splitLine.at(1);
      transform->pX = atof(splitLine.at(2).c_str());
      transform->pY = atof(splitLine.at(3).c_str());
      transform->pZ = atof(splitLine.at(4).c_str());
      transform->rX = atof(splitLine.at(5).c_str());
      transform->rY = atof(splitLine.at(6).c_str());
      transform->rZ = atof(splitLine.at(7).c_str());
      animation->frames->at(animation->frames->size() - 1)->transforms->push_back(transform);
    }
  }

  return animation;
}

void Animation::save(std::string path)
{
  std::ofstream file;
  AnimationFrame* frame = NULL;
  AnimationTransform* transform = NULL;

  file.open(path.c_str());

  if(file.is_open() == false)
  {
    throw Exception("Failed to open file for writing");
  }

  for(int i = 0; i < frames->size(); i++)
  {
    file << "f" << std::endl;
    frame = frames->at(i);

    for(int j = 0; j < frame->transforms->size(); j++)
    {
      transform = frame->transforms->at(j);

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

