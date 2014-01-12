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
  playing = false;
  rootGo = new GameObject("root");
  rootGo->getTransform()->setParent(getGameObject()->getTransform());
  rootGo->getTransform()->setLocalPosition(Vector3());
  rootGo->getTransform()->setLocalRotation(Vector3());
}

void AnimatedMeshRenderer::setFrame(float frame)
{
  this->frame = frame;
}

float AnimatedMeshRenderer::getFrame()
{
  return frame;
}

bool AnimatedMeshRenderer::isPlaying()
{
  return playing;
}

void AnimatedMeshRenderer::play()
{
  if(animation == NULL)
  {
    return;
  }

  playing = true;
}

void AnimatedMeshRenderer::stop()
{
  playing = false;
  frame = 0;
}

void AnimatedMeshRenderer::onUpdate()
{
  Transform* childTransform = NULL;
  AnimationTransform* transformA = NULL;
  AnimationTransform* transformB = NULL;
  AnimationFrame* animationFrameA = NULL;
  AnimationFrame* animationFrameB = NULL;

  for(int i = 0; i < rootGo->getTransform()->getChildCount(); i++)
  {
    childTransform = rootGo->getTransform()->getChild(i);
    childTransform->setLocalPosition(mesh->getMeshOffset(i));
    childTransform->setLocalRotation(Vector3());
  }

  if(animation != NULL && animation->frames.size() > 0)
  {
    for(int i = 0; i < rootGo->getTransform()->getChildCount(); i++)
    {
      childTransform = rootGo->getTransform()->getChild(i);
      animationFrameA = &animation->frames.at(frame);

      if(frame >= animation->frames.size() - 1)
      {
        animationFrameB = &animation->frames.at(0);
        //animationFrameB = &animation->frames.at(frame);
      }
      else
      {
        animationFrameB = &animation->frames.at(frame + 1);
      }

      transformA = NULL;
      transformB = NULL;

      for(int j = 0; j < animationFrameA->transforms.size(); j++)
      {
        if(childTransform->getGameObject()->getName() == animationFrameA->transforms.at(j).partName)
        {
          transformA = &animationFrameA->transforms.at(j);
          break;
        }
      }

      if(transformA == NULL) continue;

      for(int j = 0; j < animationFrameB->transforms.size(); j++)
      {
        if(childTransform->getGameObject()->getName() == animationFrameB->transforms.at(j).partName)
        {
          transformB = &animationFrameB->transforms.at(j);
          break;
        }
      }

      if(transformB == NULL) transformB = transformA;

      Vector3 a(transformA->pX, transformA->pY, transformA->pZ);
      Vector3 b(transformB->pX, transformB->pY, transformB->pZ);
      Vector3 diff = b - a;
      float frameDiff = (float)((int)frame + 1) - frame;

      //std::cout << frameDiff << std::endl;

      childTransform->setLocalPosition(childTransform->getLocalPosition() + a + (diff * (1.0f - frameDiff)));

      a = Vector3(transformA->rX, transformA->rY, transformA->rZ);
      b = Vector3(transformB->rX, transformB->rY, transformB->rZ);
      diff = b - a;
      childTransform->setLocalRotation(a + (diff * (1.0f - frameDiff)));
    }

    if(playing == true)
    {
      frame += Time::getDeltaTime();
    }

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

