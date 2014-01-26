#include "FencePanel.h"
#include "Fence.h"

#include <iostream>

using namespace mutiny::engine;

GameObject* FencePanel::create(Fence* fence)
{
  GameObject* mainGo = new GameObject("FencePanel");
  FencePanel* fp = mainGo->addComponent<FencePanel>();
  fp->fence = fence;

  return mainGo;
}

void FencePanel::onStart()
{
  MeshRenderer* fencePanelMr = getGameObject()->addComponent<MeshRenderer>();
  Material* material = new Material(Resources::load<Material>("shaders/textured"));
  material->setMainTexture(Resources::load<Texture2d>("models/fence/fence"));
  
  MeshFilter* mf = getGameObject()->addComponent<MeshFilter>();

  mf->setMesh(fence->mesh);

  fencePanelMr->setMaterial(material);
}
