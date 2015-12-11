#include "AudioClip.h"
#include "internal/platform.h"

namespace mutiny
{

namespace engine
{

AudioClip* AudioClip::load(std::string path)
{
#ifdef USE_SDL
  AudioClip* audioClip = new AudioClip();
  audioClip->data = Chunk::LoadWAV(path + ".ogg");

  return audioClip;
#endif

  return NULL;
}

}

}

