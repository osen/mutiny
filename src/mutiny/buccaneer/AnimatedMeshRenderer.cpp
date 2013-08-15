#include "AnimatedMeshRenderer.h"
#include "AnimatedMesh.h"
#include "../GameObject.h"
#include "../MeshFilter.h"
#include "../MeshRenderer.h"
#include "../Transform.h"
#include "../Resources.h"
#include "../Texture2d.h"
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
    Mesh* m = mesh->getMesh(i);
    mf->setMesh(m);
    MeshRenderer* mr = go->addComponent<MeshRenderer>();

    std::vector<Material*> materials;
    for(int x = 0; x < m->getSubmeshCount(); x++)
    {
      Material* material = Resources::load<Material>("shaders/textured");
      Texture2d* tex = Resources::load<Texture2d>(mesh->getTexture(i, x));

      if(tex == NULL)
      {
        Debug::logError("Error: Texture is null " + mesh->getTexture(i, x));
        throw std::exception();
      }

      material->setMainTexture(Resources::load<Texture2d>(mesh->getTexture(i, x)));
      materials.push_back(material);
    }

    mr->setMaterials(materials);
  }
}

AnimatedMesh* AnimatedMeshRenderer::getAnimatedMesh()
{
  return mesh;
}

}

}

