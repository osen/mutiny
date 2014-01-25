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

  float fpLength = mesh->getBounds().size.z;
  float fenceLengthX = fpLength * FENCE_X_WIDTH;
  float fenceLengthZ = fpLength * FENCE_Z_WIDTH;

  for(int i = 0; i < FENCE_X_WIDTH; i++) 
  {
    GameObject* go = FencePanel::create(this);
    go->getTransform()->setPosition(Vector3(((i*fpLength)-fenceLengthX/2)+fpLength/2, 0, (fenceLengthZ/2)*-1));
    go->getTransform()->setRotation(Vector3(0, 90, 0));
  } 

  for (int i = 0; i < FENCE_X_WIDTH; i++) 
  {
    GameObject* go = FencePanel::create(this);
    go->getTransform()->setPosition(Vector3(((i*fpLength)-fenceLengthX/2) + fpLength/2,0,fenceLengthZ/2));
    go->getTransform()->setRotation(Vector3(0, 90, 0));
  } 

  //fpLength = mesh->getBounds().size.x;

  for (int i = 0; i < FENCE_Z_WIDTH; i++) 
  {
    GameObject* go = FencePanel::create(this);
    go->getTransform()->setPosition(Vector3(fenceLengthX/2,0,((i*fpLength)-fenceLengthZ/2)+ fpLength/2));
  } 

  for (int i = 0; i < FENCE_Z_WIDTH; i++) 
  {
    GameObject* go = FencePanel::create(this);
    go->getTransform()->setPosition(Vector3((fenceLengthX/2)*-1,0,((i*fpLength)-fenceLengthZ/2)+ fpLength/2));
  } 
}





//  GameObject* go = FencePanel::create(this);
//  FencePanel* fp = go->getComponent<FencePanel>();
//  float fpLength = fp->getComponent()->getBounds()->size->x;
