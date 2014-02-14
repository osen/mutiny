#include "Audio.h"

#include <mutiny/mutiny.h>
#include <SDL/SDL.h>
#include <iostream>

using namespace mutiny::engine;

#ifndef WINDOWS
std::vector<Mix_Chunk*> Audio::sounds;
Mix_Music* Audio::music = NULL;
Mix_Music* Audio::musicA = NULL;
Mix_Music* Audio::breathing = NULL;
#endif

void Audio::initialize()
{
#ifndef WINDOWS
  int audio_rate = 22050;
  int audio_channels = 2;
  int audio_buffers = 1024;
  Uint16 audio_format = MIX_DEFAULT_FORMAT;

  SDL_InitSubSystem(SDL_INIT_AUDIO);

  if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) == -1)
  {
    std::cout << "Audio failed to initialize" << std::endl;
    throw std::exception();
  }

  // Load audio files
  addSound("audio/Ambient_2.ogg");
  addSound("audio/Ambient_1.ogg");
  addSound("audio/Ambient_2.ogg");
  addSound("audio/Ambient_3.ogg");
  addSound("audio/Ambient_4.ogg");
  addSound("audio/Ambient_5.ogg");
//
  addSound("audio/Horny_4.ogg");
//
  addSound("audio/Wolf_Growl_1.ogg");
  addSound("audio/Wolf_Growl_2.ogg");
  addSound("audio/Wolf_Growl_3.ogg");
  addSound("audio/Wolf_Growl_4.ogg");
  addSound("audio/Wolf_Growl_5.ogg");
//
  addSound("audio/Wolf_1.ogg");
  addSound("audio/Wolf_2.ogg");
  addSound("audio/Wolf_3.ogg");
  addSound("audio/Wolf_4.ogg");
//
  addSound("audio/VoiceIntro_1.ogg");
//
  addSound("audio/Horny_1.ogg");
  addSound("audio/Horny_2.ogg");
  addSound("audio/Horny_3.ogg");
  addSound("audio/Horny_4.ogg");
  addSound("audio/Horny_5.ogg");
  addSound("audio/Horny_6.ogg");
//
  addSound("audio/Scream_1.ogg");

  music = Mix_LoadMUS(std::string(Application::getDataPath() + "/audio/menuMusic.ogg").c_str());
  musicA = Mix_LoadMUS(std::string(Application::getDataPath() + "/audio/Bird_ambience.ogg").c_str());
  breathing = Mix_LoadMUS(std::string(Application::getDataPath() + "/audio/Heavy_Breathing.ogg").c_str());
#endif
}

void Audio::addSound(std::string path)
{
#ifndef WINDOWS
  sounds.push_back(Mix_LoadWAV(std::string(Application::getDataPath() + "/" + path).c_str()));
#endif
}

void Audio::playSound(int sound)
{
#ifndef WINDOWS
  Mix_PlayChannel(-1,sounds[sound],0);
#endif
}

void Audio::playMusic()
{
#ifndef WINDOWS
  Mix_PlayMusic(music, -1);
#endif
}

void Audio::playMusicA()
{
#ifndef WINDOWS
  Mix_PlayMusic(musicA, -1);
#endif
}

void Audio::playBreathing()
{
#ifndef WINDOWS
  Mix_PlayMusic(breathing, -1);
#endif
}

void Audio::stopMusic()
{
#ifndef WINDOWS
  Mix_HaltMusic();
#endif
}


/*
Audio::~Audio()
{
  for(int i = 0; i < sounds.size(); i++)
    Mix_FreeChunk(sounds[i]);

  Mix_CloseAudio();
  SDL_QuitSubSystem(SDL_INIT_AUDIO);
}
*/
