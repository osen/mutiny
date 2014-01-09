#include "AnimatedMeshRenderer.h"
#include "AnimatedMesh.h"
#include "Animation.h"
#include "../GameObject.h"
#include "../MeshFilter.h"
#include "../MeshRenderer.h"
#include "../Transform.h"
#include "../Resources.h"
#include "../Texture2d.h"
#include "../Shader.h"
#include "../Vector3.h"
#include "../Time.h"
#include "../Debug.h"

namespace mutiny
{

namespace engine
{

void AnimatedMeshRenderer::onAwake()
{
  mesh = NULL;
  animation = NULL;
  frame = 0;
  rootGo = new GameObject("root");
  rootGo->getTransform()->setParent(getGameObject()->getTransform());
  rootGo->getTransform()->setLocalPosition(Vector3());
}

void AnimatedMeshRenderer::onUpdate()
{
  Transform* childTransform = NULL;

  for(int i = 0; i < rootGo->getTransform()->getChildCount(); i++)
  {
    childTransform = rootGo->getTransform()->getChild(i);
    childTransform->setLocalPosition(mesh->getMeshOffset(i));
  }

  if(animation != NULL && animation->frames.size() > 0)
  {
    for(int i = 0; i < rootGo->getTransform()->getChildCount(); i++)
    {
      childTransform = rootGo->getTransform()->getChild(i);
      AnimationFrame* animationFrame = &animation->frames.at(frame);

      for(int j = 0; j < animationFrame->transforms.size(); j++)
      {
        AnimationTransform* transform = &animationFrame->transforms.at(j);

        if(childTransform->getGameObject()->getName() == transform->partName)
        {
          childTransform->setLocalPosition(Vector3(transform->pX, transform->pY, transform->pZ));
        }
      }
    }

    frame += Time::getDeltaTime();

    if(frame >= animation->frames.size())
    {
      frame = 0;
    }
  }
}

void AnimatedMeshRenderer::setAnimatedMesh(AnimatedMesh* mesh)
{
  this->mesh = mesh;
  materials.clear();

  for(int i = 0; i < mesh->getMeshCount(); i++)
  {
    GameObject* go = new GameObject(mesh->getMeshName(i));
    go->getTransform()->setParent(rootGo->getTransform());
    go->getTransform()->setLocalPosition(mesh->getMeshOffset(i));
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

Animation* AnimatedMeshRenderer::getAnimation()
{
  return animation;
}

void AnimatedMeshRenderer::setAnimation(Animation* animation)
{
  this->animation = animation;
}

}

}

