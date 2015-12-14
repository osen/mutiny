#include "AudioSource.h"
#include "AudioClip.h"
#include "Vector3.h"
#include "internal/platform.h"

#ifdef USE_SDL
  #include <SDL/SDL_mixer.h>
#endif

#include <iostream>

namespace mutiny
{

namespace engine
{

void AudioSource::playClipAtPoint(arc<AudioClip> audioClip, Vector3 position)
{
#ifdef USE_SDL
  Mix_PlayChannel(-1, audioClip->data->data, 0);
#endif
}

}

}

