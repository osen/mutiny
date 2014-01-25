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
  sounds.push_back(Mix_LoadWAV(std::string(Application::getDataPath() + "/audio/baa.wav").c_str()));
  sounds.push_back(Mix_LoadWAV(std::string(Application::getDataPath() + "/audio/stressedBaa.wav").c_str()));
}

void Audio::playSound(int sound)
{
  Mix_PlayChannel(-1,sounds[sound],0); 
}

Audio::~Audio()
{
  Mix_FreeChunk(sounds[0]);
  Mix_FreeChunk(sounds[1]);

  Mix_CloseAudio();
  SDL_QuitSubSystem(SDL_INIT_AUDIO);
}
