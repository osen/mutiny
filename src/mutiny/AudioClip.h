#ifndef MUTINY_ENGINE_AUDIOCLIP_H
#define MUTINY_ENGINE_AUDIOCLIP_H

#include "Object.h"
#include "internal/platform.h"
#include "arc.h"

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

#ifdef USE_SDL
class Chunk
{
public:
  static arc<Chunk> LoadWAV(std::string path)
  {
    arc<Chunk> rtn = arc<Chunk>::alloc();
    rtn->data = Mix_LoadWAV(path.c_str());

    if(rtn->data == NULL)
    {
      throw std::exception();
    }

    return rtn;
  }

  ~Chunk()
  {
    if(data != NULL)
    {
      Mix_FreeChunk(data);
    }
  }

//private:
  Mix_Chunk* data;

};
#endif

class AudioClip : public Object
{
  friend class mutiny::engine::Resources;
  friend class mutiny::engine::AudioSource;

private:
  static AudioClip* load(std::string path);

#ifdef USE_SDL
  arc<Chunk> data;
#endif

};

}

}

#endif

