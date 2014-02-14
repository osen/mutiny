#ifndef AUDIO_H
#define AUDIO_H

#ifndef WINDOWS
#include <SDL/SDL_mixer.h>
#endif
#include <vector>
#include <string>

class Audio
{
public:
  static void initialize();

  static void addSound(std::string path);
  static void playSound(int sound);
  static void playMusic();
  static void playMusicA();
  static void playBreathing();
  static void stopMusic();

private:
#ifndef WINDOWS
  static std::vector<Mix_Chunk*> sounds;
  static Mix_Music* music;
  static Mix_Music* musicA;
  static Mix_Music* breathing;
#endif

};

#endif
