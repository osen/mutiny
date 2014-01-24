#include "Fence.h"

#include <iostream>

using namespace mutiny::engine;

GameObject* Fence::create()
{
  GameObject* mainGo = new GameObject("Fence");
  mainGo->addComponent<Fence>();

  return mainGo;
}

void Fence::onUpdate()
{
  Debug::log("Feeeeennce");
}
