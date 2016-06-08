#include "FencePanel.h"
#include "Fence.h"

#include <iostream>

using namespace mutiny::engine;

ref<GameObject> FencePanel::create(ref<Fence> fence)
{
  ref<GameObject> mainGo = GameObject::create("FencePanel");
  ref<FencePanel> fp = mainGo->addComponent<FencePanel>();
  fp->fence = fence;

  return mainGo;
}

void FencePanel::onStart()
{
  ref<MeshRenderer> fencePanelMr = getGameObject()->addComponent<MeshRenderer>();
  material = Material::create(Resources::load<Shader>("shaders/Internal-MeshRendererTexture"));
  material->setMainTexture(Resources::load<Texture2d>("models/fence/fence"));
  
  ref<MeshFilter> mf = getGameObject()->addComponent<MeshFilter>();

  mf->setMesh(fence->mesh);

  fencePanelMr->setMaterial(material);
}
