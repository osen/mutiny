#include "AudioClip.h"

#include <SDL/SDL_mixer.h>

namespace mutiny
{

namespace engine
{

AudioClip* AudioClip::load(std::string path)
{
  Mix_Chunk* data = NULL;

  data = Mix_LoadWAV(std::string(path + ".ogg").c_str());

  if(data == NULL)
  {
    throw std::exception();
  }

  AudioClip* audioClip = new AudioClip();
  audioClip->data.reset(data, Mix_FreeChunk);

  return audioClip;
}

}

}

