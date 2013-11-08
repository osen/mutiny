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
      Material* material = NULL;

      Texture* tex = mesh->getTexture(i, x);

      if(tex != NULL)
      {
        material = new Material(Resources::load<Shader>("shaders/textured"));
        material->setMainTexture(tex);
      }
      else
      {
        material = new Material(Resources::load<Shader>("shaders/default_diffuse"));
      }

      materials.push_back(std::unique_ptr<Material>(material));
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

