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
    go->getTransform()->setParent(rootGo->getTransform());
    MeshFilter* mf = go->addComponent<MeshFilter>();
    Mesh* m = mesh->getMesh(i);
    mf->setMesh(m);
    MeshRenderer* mr = go->addComponent<MeshRenderer>();

    std::vector<Material*> newMaterials;
    for(int x = 0; x < m->getSubmeshCount(); x++)
    {
      Material* material = new Material(Resources::load<Shader>("shaders/textured"));
      Texture2d* tex = Resources::load<Texture2d>(mesh->getTexture(i, x));

      if(tex == NULL)
      {
        Debug::logError("Error: Texture is null " + mesh->getTexture(i, x));
        throw std::exception();
      }

      material->setMainTexture(Resources::load<Texture2d>(mesh->getTexture(i, x)));
      newMaterials.push_back(material);
      materials.push_back(std::unique_ptr<Material>(material));
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

