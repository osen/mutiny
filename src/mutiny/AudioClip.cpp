#include "AudioClip.h"
#include "Application.h"
#include "internal/platform.h"
#include "Debug.h"

namespace mutiny
{

namespace engine
{

ref<AudioClip> AudioClip::load(std::string path)
{
  ref<AudioClip> audioClip = new AudioClip();
#ifdef USE_SDL
  audioClip->data = Chunk::LoadWAV(path + ".ogg");
#endif

  return audioClip;
}

}

}

