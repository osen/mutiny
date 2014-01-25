#include "Fence.h"
#include "FencePanel.h"

#include <iostream>

using namespace mutiny::engine;

GameObject* Fence::create()
{
  GameObject* mainGo = new GameObject("Fence");
  mainGo->addComponent<Fence>();

  return mainGo;
}

void Fence::onAwake()
{
  mesh = Resources::load<Mesh>("models/fence/fence");
  float fpLength = mesh->getBounds().size.x;

  //FencePanel* []
}





//  GameObject* go = FencePanel::create(this);
//  FencePanel* fp = go->getComponent<FencePanel>();
//  float fpLength = fp->getComponent()->getBounds()->size->x;
