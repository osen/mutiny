#include "AudioClip.h"
#include "internal/platform.h"

namespace mutiny
{

namespace engine
{

AudioClip* AudioClip::load(std::string path)
{
  AudioClip* audioClip = new AudioClip();
#ifdef USE_SDL
  audioClip->data = Chunk::LoadWAV(path + ".ogg");
#endif

  return audioClip;
}

}

}

