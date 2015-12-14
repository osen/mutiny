#include "SceneManager.h"

#include <mutiny/mutiny.h>

#include <ctime>

using namespace mutiny::engine;

void mutiny_main()
{
  srand(time(NULL));
  Application::setTitle("Baastud - The quadrupedal, copulation game");

  GameObject* smGo = new GameObject();
  smGo->addComponent<SceneManager>();

  Application::loadLevel("mutiny");
}
