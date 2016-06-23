#include "SceneManager.h"

#include <mutiny/mutiny.h>

using namespace mutiny::engine;

void mutiny_main()
{
  ref<GameObject> smGo = GameObject::create();
  smGo->addComponent<SceneManager>();
}

