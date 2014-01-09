#include "Animation.h"

#include "../internal/Util.h"

#include <fstream>
#include <memory>

namespace mutiny
{

namespace engine
{

Animation* Animation::load(std::string path)
{
  std::string line;
  std::ifstream file;
  std::vector<std::string> splitLine;
  std::unique_ptr<Animation> animation;

  animation.reset(new Animation());
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
      animation->frames.push_back(AnimationFrame());
    }
    else if(splitLine.at(0) == "t")
    {
      AnimationTransform transform;
      transform.partName = splitLine.at(1);
      transform.pX = atof(splitLine.at(2).c_str());
      transform.pY = atof(splitLine.at(3).c_str());
      transform.pZ = atof(splitLine.at(4).c_str());
      transform.rX = atof(splitLine.at(5).c_str());
      transform.rY = atof(splitLine.at(6).c_str());
      transform.rZ = atof(splitLine.at(7).c_str());
      animation->frames.at(animation->frames.size() - 1).transforms.push_back(transform);
    }
  }

  return animation.release();
}

}

}

