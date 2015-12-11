#ifndef MUTINY_ENGINE_AUDIOCLIP_H
#define MUTINY_ENGINE_AUDIOCLIP_H

#include "Object.h"
#include "internal/platform.h"

#ifdef USE_SDL
  #include <SDL/SDL_mixer.h>
#endif

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

#ifdef USE_SDL
  arc<Mix_Chunk> data;
#endif

};

}

}

#endif

