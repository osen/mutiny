#include "FencePanel.h"
#include "Fence.h"

#include <iostream>

using namespace mutiny::engine;

GameObject* FencePanel::create(Fence* fence)
{
  GameObject* mainGo = gcnew<GameObject>("FencePanel");
  FencePanel* fp = mainGo->addComponent<FencePanel>();
  fp->fence = fence;

  return mainGo;
}

void FencePanel::onStart()
{
  MeshRenderer* fencePanelMr = getGameObject()->addComponent<MeshRenderer>();
  Material* material = Material::create(Resources::load<Shader>("shaders/Internal-MeshRendererTexture"));
  material->setMainTexture(Resources::load<Texture2d>("models/fence/fence"));
  
  MeshFilter* mf = getGameObject()->addComponent<MeshFilter>();

  mf->setMesh(fence->mesh);

  fencePanelMr->setMaterial(material);
}
