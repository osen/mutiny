#include "SceneManager.h"

#include <mutiny/mutiny.h>

using namespace mutiny::engine;

void mutiny_main()
{
  Application::loadLevel("introduction");

  GameObject* smGo = new GameObject();
  smGo->addComponent<SceneManager>();
}

