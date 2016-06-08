#include "SceneManager.h"

#include <mutiny/mutiny.h>

using namespace mutiny::engine;

void mutiny_main()
{
  Application::loadLevel("introduction");

  ref<GameObject> smGo = GameObject::create();
  smGo->addComponent<SceneManager>();
}

