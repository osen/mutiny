#include "Sheep.h"

#include <iostream>

using namespace mutiny::engine;

GameObject* Sheep::create()
{
  GameObject* mainGo = new GameObject("Sheep");
  mainGo->addComponent<Sheep>();

  return mainGo;
}

void Sheep::onUpdate()
{
  Debug::log("Baaaaaaa");
}
