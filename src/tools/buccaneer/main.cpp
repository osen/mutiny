#include "SceneManager.h"

#include <mutiny/mutiny.h>

using namespace mutiny::engine;

void mutiny_main()
{
  GameObject* smGo = gcnew<GameObject>();
  smGo->addComponent<SceneManager>();
}

