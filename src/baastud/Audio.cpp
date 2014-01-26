#include "Audio.h"

#include <mutiny/mutiny.h>
#include <SDL/SDL.h>
#include <iostream>

using namespace mutiny::engine;

std::vector<Mix_Chunk*> Audio::sounds;
Mix_Music* Audio::music = NULL;
Mix_Music* Audio::musicA = NULL;

void Audio::initialize()
{
  int audio_rate = 22050;
  Uint16 audio_format = AUDIO_S16; /* 16-bit stereo */
  int audio_channels = 2;
  int audio_buffers = 4096;

  SDL_InitSubSystem(SDL_INIT_AUDIO);

  if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers)) 
    std::cout << "Audio ain't gunna werk :(" << std::endl;

  // Load audio files
  //addSound("audio/baa.wav");
  addSound("audio/Ambient_2.ogg");
  addSound("audio/Ambient_1.ogg");
  addSound("audio/Ambient_2.ogg");
  addSound("audio/Ambient_3.ogg");
  addSound("audio/Ambient_4.ogg");
  addSound("audio/Ambient_5.ogg");
//
  //addSound("audio/stressedBaa.wav");
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
  //addSound("audio/Heavy_Breathing.ogg");

  music = Mix_LoadMUS(std::string(Application::getDataPath() + "/audio/menuMusic.ogg").c_str());
  musicA = Mix_LoadMUS(std::string(Application::getDataPath() + "/audio/Bird_ambience.ogg").c_str());
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

void Audio::playMusicA()
{
  Mix_PlayMusic(musicA, -1);
}

void Audio::stopMusic()
{
  Mix_HaltMusic();
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
