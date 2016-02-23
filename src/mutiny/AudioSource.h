#ifndef MUTINY_ENGINE_AUDIOSOURCE_H
#define MUTINY_ENGINE_AUDIOSOURCE_H

#include "Vector3.h"

namespace mutiny
{

namespace engine
{

class AudioClip;
class AudioSource
{
public:
  static void playClipAtPoint(AudioClip* audioClip, Vector3 position);

};

}

}

#endif

