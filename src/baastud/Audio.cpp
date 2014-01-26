#include "Audio.h"

#include <mutiny/mutiny.h>
#include <SDL/SDL.h>
#include <iostream>

using namespace mutiny::engine;

Audio::Audio()
{
  int audio_rate = 22050;
  Uint16 audio_format = AUDIO_S16; /* 16-bit stereo */
  int audio_channels = 2;
  int audio_buffers = 4096;

  SDL_InitSubSystem(SDL_INIT_AUDIO);

  if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers)) 
    std::cout << "Audio ain't gunna werk :(" << std::endl;

  // Load audio files
  addSound("audio/baa.wav");
  addSound("audio/stressedBaa.wav");

  music = Mix_LoadMUS(std::string(Application::getDataPath() + "/audio/menuMusic.ogg").c_str());
  //music = Mix_LoadMUS(std::string(Application::getDataPath() + "/audio/music.ogg").c_str()));
}

void Audio::addSound(std::string path)
{
  sounds.push_back(Mix_LoadWAV(std::string(Application::getDataPath() + "/" + path).c_str()));
}

void Audio::playSound(int sound)
{
  Mix_PlayChannel(-1,sounds[sound],0); 
}

void Audio::playMusic()
{
  Mix_PlayMusic(music, -1);
}

Audio::~Audio()
{
  for(int i = 0; i < sounds.size(); i++)
    Mix_FreeChunk(sounds[i]);

  Mix_CloseAudio();
  SDL_QuitSubSystem(SDL_INIT_AUDIO);
}
