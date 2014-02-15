#include "AudioSource.h"
#include "AudioClip.h"
#include "Vector3.h"

#include <SDL/SDL_mixer.h>

#include <iostream>

namespace mutiny
{

namespace engine
{

void AudioSource::playClipAtPoint(AudioClip* audioClip, Vector3 position)
{
  Mix_PlayChannel(-1, audioClip->data.get(), 0);
}

}

}

