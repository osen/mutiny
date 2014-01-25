#include "Transform.h"
#include "Vector2.h"
#include "Matrix4x4.h"
#include "GameObject.h"
#include "Debug.h"

#include "glm/glm.hpp"
#include "glm/ext.hpp"

namespace mutiny
{

namespace engine
{

Transform::~Transform()
{

}

void Transform::onAwake()
{
  //Debug::log("Transform awake");
  parent = NULL;
}

void Transform::onDestroy()
{
  detachChildren();
  setParent(NULL);
}

void Transform::setLocalRotation(Vector3 rotation)
{
  localRotation = rotation;
}

void Transform::setLocalPosition(Vector3 position)
{
  // Take off parent's existing position. Use setLocalPosition to set directly.
  localPosition = position;
}

Vector3 Transform::getLocalPosition()
{
  return localPosition;
}

Vector3 Transform::getLocalRotation()
{
  return localRotation;
}

void Transform::setRotation(Vector3 rotation)
{
  if(getParent() != NULL)
  {
    localRotation = rotation - getParent()->getRotation();
  }
  else
  {
    localRotation = rotation;
  }
}

void Transform::setPosition(Vector3 position)
{
  if(getParent() != NULL)
  {
    Matrix4x4 trs = Matrix4x4::getIdentity();
    Transform* trans = getParent();

    while(trans != NULL)
    {
      trs = Matrix4x4::getTrs(trans->localPosition, trans->localRotation, Vector3(1, 1, 1)) * trs;
      trans = trans->getParent();
    }

    localPosition = trs.inverse() * position;
  }
  else
  {
    localPosition = position;
  }
}

Vector3 Transform::getPosition()
{
  Matrix4x4 trs = Matrix4x4::getIdentity();
  Transform* trans = this;

  while(trans != NULL)
  {
    trs = Matrix4x4::getTrs(trans->localPosition, trans->localRotation, Vector3(1, 1, 1)) * trs;
    trans = trans->getParent();
  }

  return trs * Vector3();
}

Vector3 Transform::getRotation()
{
  Transform* trans = this;
  Vector3 rotation;

  while(trans != NULL)
  {
    rotation = rotation + trans->localRotation;
    trans = trans->getParent();
  }

  return rotation;
}

void Transform::detachChildren()
{
  std::vector<Transform*> tmpChildren = children;

  for(int i = 0; i < tmpChildren.size(); i++)
  {
    tmpChildren.at(i)->setParent(NULL);
    // Dont just detach.. destroy
    Object::destroy(tmpChildren.at(i)->getGameObject());
  }

  // Just to make sure.
  children.clear();
}

Transform* Transform::find(std::string name)
{
  for(int i = 0; i < children.size(); i++)
  {
    if(children.at(i)->getGameObject()->getName() == name)
    {
      return children.at(i);
    }
  }

  return NULL;
}

Transform* Transform::getParent()
{
  return parent;
}

void Transform::setParent(Transform* transform)
{
  if(this->parent != NULL)
  {
    for(int i = 0; i < this->parent->children.size(); i++)
    {
      if(this->parent->children.at(i) == this)
      {
        this->parent->children.erase(this->parent->children.begin() + i);
        break;
      }
    }
  }

  if(transform != NULL)
  {
    transform->children.push_back(this);
  }

  setLocalPosition(getPosition());
  setLocalRotation(getRotation());
  this->parent = transform;
  setPosition(getLocalPosition());
  setRotation(getLocalRotation());
}

int Transform::getChildCount()
{
  return children.size();
}

Transform* Transform::getChild(int index)
{
  return children.at(index);
}

Transform* Transform::getRoot()
{
  Transform* root = this;
  Transform* trans = parent;

  while(trans != NULL)
  {
    root = trans;
    trans = trans->getParent();
  }

  return root;
}

void Transform::rotate(Vector3 eulerAngles)
{
  localRotation.x += eulerAngles.x;
  localRotation.y += eulerAngles.y;
  localRotation.z += eulerAngles.z;
}

void Transform::translate(Vector3 translation)
{
  localPosition.x += translation.x;
  localPosition.y += translation.y;
  localPosition.z += translation.z;
}

void Transform::lookAt(Vector3 worldPosition)
{
  //Vector3 diff = Vector3(localPosition.x, localPosition.y, localPosition.z) - Vector3(worldPosition.x, worldPosition.y, worldPosition.z);

  //float angle = atan2(diff.y, sqrt(diff.x * diff.x + diff.z * diff.z)) * 180.0f / 3.14159265359f;
  //float angle = atan2(diff.y, diff.x) * 180.0f / 3.14159265359f;
  //localRotation.x = angle - 180.0f;
  //localRotation.x = 180 - (180 + angle);
  //localRotation.x = angle;

  //std::cout << angle << std::endl;

  //std::cout << localRotation.x << std::endl;

  Vector2 diff2 = Vector2(localPosition.x, localPosition.z) - Vector2(worldPosition.x, worldPosition.z);

  float angle = atan2(diff2.x, diff2.y) * 180 / 3.14159265359f;
  localRotation.y = angle - 180.0f;
}

// Should use Matrix4x4 rather than the unwrapped glm.
void Transform::rotateAround(Vector3 center, Vector3 axis, float amount)
{
  glm::mat4 mat;

  mat = glm::translate(mat, glm::vec3(center.x, center.y, center.z));
  mat = glm::rotate(mat, amount, glm::vec3(axis.x, axis.y, axis.z));
  mat = glm::translate(mat, -glm::vec3(center.x, center.y, center.z));
  mat = glm::translate(mat, glm::vec3(localPosition.x, localPosition.y, localPosition.z));
  glm::vec4 out = mat * glm::vec4(glm::vec3(), 1.0f);

  localPosition.x = out.x;
  localPosition.y = out.y;
  localPosition.z = out.z;

  //std::cout << localPosition.x << " " << localPosition.z << std::endl;
}

Vector3 Transform::getForward()
{
  Matrix4x4 m = Matrix4x4::getTrs(localPosition, localRotation, Vector3(1, 1, 1));

  return m.multiplyVector(Vector3(0, 0, 1));  
}

}

}

