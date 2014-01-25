#ifndef AUDIO_H
#define AUDIO_H

#include <SDL/SDL_mixer.h>
#include <vector>
#include <string>

class Audio
{
public:
  Audio();
  ~Audio();

  void addSound(std::string path);
  void playSound(int sound);
  void playMusic();
private:
  std::vector<Mix_Chunk*> sounds;
  Mix_Music* music;

};

#endif
