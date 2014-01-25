#ifndef AUDIO_H
#define AUDIO_H

#include <SDL/SDL_mixer.h>
#include <vector>

class Audio
{
public:
  Audio();
  ~Audio();

  void playSound(int sound);
private:
  std::vector<Mix_Chunk*> sounds;

};

#endif
