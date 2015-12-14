#ifndef MUTINY_ENGINE_AUDIOSOURCE_H
#define MUTINY_ENGINE_AUDIOSOURCE_H

#include "Vector3.h"
#include "arc.h"

namespace mutiny
{

namespace engine
{

class AudioClip;
class AudioSource
{
public:
  static void playClipAtPoint(arc<AudioClip> audioClip, Vector3 position);

};

}

}

#endif

