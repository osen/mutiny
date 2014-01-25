#include "AudioTest.h"
#include "Audio.h"

#include <iostream>

using namespace mutiny::engine;

GameObject* AudioTest::create()
{
  GameObject* mainGo = new GameObject("AudioTest");
  mainGo->addComponent<AudioTest>();

  return mainGo;
}

void AudioTest::onAwake()
{
  audio.reset(new Audio());
}

void AudioTest::onGui()
{
  Gui::label(Rect(100, 10, 100, 100), "baaaaaaaaaaaaasttuuuuddd");

  if(Gui::button(Rect(300, 200, 200, 50), "test 1") == true)
  {
		Debug::log("Play baa");
    audio->playSound(0);
  }
  else if(Gui::button(Rect(300, 300, 200, 50), "test 2") == true)
  {
		Debug::log("Play stressed baa");
    audio->playSound(1);
  }
  else if(Gui::button(Rect(300, 400, 200, 50), "test 2") == true)
  {
		Debug::log("Play music loop");
    audio->playMusic();
  }
  else if(Gui::button(Rect(500, 500, 200, 50), "quit") == true)
  {
		Application::quit();
  }
}

