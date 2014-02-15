#ifndef MUTINY_ENGINE_AUDIOCLIP_H
#define MUTINY_ENGINE_AUDIOCLIP_H

#include "Object.h"

#include <SDL/SDL_mixer.h>

#include <memory>

namespace mutiny
{

namespace engine
{

class AudioSource;
class Resources;

class AudioClip : public Object
{
  friend class mutiny::engine::Resources;
  friend class mutiny::engine::AudioSource;

private:
  static AudioClip* load(std::string path);

  std::shared_ptr<Mix_Chunk> data;

};

}

}

#endif

