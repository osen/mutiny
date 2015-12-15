#ifndef AUDIO_H
#define AUDIO_H

#include <mutiny/mutiny.h>

//#include <SDL/SDL_mixer.h>
#include <vector>
#include <string>

using namespace mutiny::engine;

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
  static std::vector<arc<AudioClip> > sounds;
  //static Mix_Music* music;
  //static Mix_Music* musicA;
  //static Mix_Music* breathing;

};

#endif
