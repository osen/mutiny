#include "AudioClip.h"
#include "Application.h"
#include "internal/platform.h"
#include "Debug.h"

namespace mutiny
{

namespace engine
{

AudioClip* AudioClip::load(std::string path)
{
  AudioClip* audioClip = Application::getGC()->gc_new<AudioClip>();
#ifdef USE_SDL
  audioClip->data = Chunk::LoadWAV(path + ".ogg");
#endif

  return audioClip;
}

}

}

