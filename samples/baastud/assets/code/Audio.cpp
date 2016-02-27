#include "Audio.h"

#include <mutiny/mutiny.h>
//#include <SDL/SDL.h>

#include <iostream>

using namespace mutiny::engine;

Audio* Audio::self = NULL;

void Audio::initialize()
{
  if(self == NULL)
  {
    GameObject* audioGo = gcnew<GameObject>("AudioSystem");
    Audio* audio = audioGo->addComponent<Audio>();
    audio->sounds = gcnewlist<AudioClip*>();
    Object::dontDestroyOnLoad(audioGo);
    self = audio;
  }

  self->sounds->clear();
  // Load audio files
  addSound("audio/Ambient_2");
  addSound("audio/Ambient_1");
  addSound("audio/Ambient_2");
  addSound("audio/Ambient_3");
  addSound("audio/Ambient_4");
  addSound("audio/Ambient_5");
//
  addSound("audio/Horny_4");
//
  addSound("audio/Wolf_Growl_1");
  addSound("audio/Wolf_Growl_2");
  addSound("audio/Wolf_Growl_3");
  addSound("audio/Wolf_Growl_4");
  addSound("audio/Wolf_Growl_5");
//
  addSound("audio/Wolf_1");
  addSound("audio/Wolf_2");
  addSound("audio/Wolf_3");
  addSound("audio/Wolf_4");
//
  addSound("audio/VoiceIntro_1");
//
  addSound("audio/Horny_1");
  addSound("audio/Horny_2");
  addSound("audio/Horny_3");
  addSound("audio/Horny_4");
  addSound("audio/Horny_5");
  addSound("audio/Horny_6");
//
  addSound("audio/Scream_1");

/*
  if(music == NULL) music = Mix_LoadMUS(std::string(Application::getDataPath() + "/audio/menuMusic.ogg").c_str());
  if(musicA == NULL) musicA = Mix_LoadMUS(std::string(Application::getDataPath() + "/audio/Bird_ambience.ogg").c_str());
  if(breathing == NULL) breathing = Mix_LoadMUS(std::string(Application::getDataPath() + "/audio/Heavy_Breathing.ogg").c_str());
*/
}

void Audio::addSound(std::string path)
{
  AudioClip* clip = Resources::load<AudioClip>(path);

  if(clip == NULL)
  {
    throw std::exception();
  }

  self->sounds->push_back(clip);
}

void Audio::playSound(int sound)
{
  AudioSource::playClipAtPoint(self->sounds->at(sound), Vector3());
}

void Audio::playMusic()
{
  //Mix_PlayMusic(music, -1);
}

void Audio::playMusicA()
{
  //Mix_PlayMusic(musicA, -1);
}

void Audio::playBreathing()
{
  //Mix_PlayMusic(breathing, -1);
}

void Audio::stopMusic()
{
  //Mix_HaltMusic();
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

