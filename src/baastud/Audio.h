#ifndef AUDIO_H
#define AUDIO_H

#include <SDL/SDL_mixer.h>
#include <vector>
#include <string>

class Audio
{
public:
  static void initialize();

  static void addSound(std::string path);
  static void playSound(int sound);
  static void playMusic();

private:
  static std::vector<Mix_Chunk*> sounds;
  static Mix_Music* music;

};

#endif
