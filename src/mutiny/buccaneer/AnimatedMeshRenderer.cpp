#include "AnimatedMeshRenderer.h"
#include "AnimatedMesh.h"
#include "../GameObject.h"
#include "../MeshFilter.h"
#include "../MeshRenderer.h"
#include "../Transform.h"
#include "../Debug.h"

namespace mutiny
{

namespace engine
{

void AnimatedMeshRenderer::onAwake()
{
  Debug::log("AnimatedMeshRenderer awaken");
  mesh = NULL;
  rootGo = new GameObject("root");
  rootGo->getTransform()->setParent(getGameObject()->getTransform());
}

void AnimatedMeshRenderer::setAnimatedMesh(AnimatedMesh* mesh)
{
  this->mesh = mesh;

  for(int i = 0; i < mesh->getMeshCount(); i++)
  {
    GameObject* go = new GameObject("part");
    go->getTransform()->setParent(rootGo->getTransform());
    MeshFilter* mf = go->addComponent<MeshFilter>();
    mf->setMesh(mesh->getMesh(i));
    MeshRenderer* mr = go->addComponent<MeshRenderer>();
  }
}

AnimatedMesh* AnimatedMeshRenderer::getAnimatedMesh()
{
  return mesh;
}

}

}

