#include "AnimatedMeshRenderer.h"
#include "AnimatedMesh.h"
#include "../GameObject.h"
#include "../MeshFilter.h"
#include "../MeshRenderer.h"
#include "../Transform.h"
#include "../Resources.h"
#include "../Texture2d.h"
#include "../Shader.h"
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
  materials.clear();

  for(int i = 0; i < mesh->getMeshCount(); i++)
  {
    GameObject* go = new GameObject(mesh->getMeshName(i));
    Vector3 offset = mesh->getMeshOffset(i);
    go->getTransform()->setParent(rootGo->getTransform());
    go->getTransform()->setLocalPosition(offset);
    MeshFilter* mf = go->addComponent<MeshFilter>();
    Mesh* m = mesh->getMesh(i);
    mf->setMesh(m);
    MeshRenderer* mr = go->addComponent<MeshRenderer>();

    std::vector<Material*> newMaterials;
    for(int x = 0; x < m->getSubmeshCount(); x++)
    {
      Material* material = new Material(Resources::load<Shader>("shaders/textured"));
      materials.push_back(std::unique_ptr<Material>(material));
      material->setMainTexture(mesh->getTexture(i, x));
      newMaterials.push_back(material);
    }

    mr->setMaterials(newMaterials);
  }
}

AnimatedMesh* AnimatedMeshRenderer::getAnimatedMesh()
{
  return mesh;
}

}

}

