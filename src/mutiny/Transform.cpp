#include "Transform.h"
#include "Vector2.h"
#include "Matrix4x4.h"
#include "GameObject.h"
#include "Debug.h"

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
  localScale = Vector3(1, 1, 1);
  children = Application::getGC()->gc_list<Transform*>();
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

void Transform::setLocalScale(Vector3 scale)
{
  localScale = scale;
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

void Transform::setScale(Vector3 scale)
{
  if(getParent() != NULL)
  {
    Matrix4x4 trs = Matrix4x4::getIdentity();
    Transform* trans = getParent();

    while(trans != NULL)
    {
      trs = Matrix4x4::getTrs(trans->localPosition, trans->localRotation, trans->localScale) * trs;
      trans = trans->getParent();
    }

    localScale = trs.inverse() * scale;
  }
  else
  {
    localScale = scale;
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

Vector3 Transform::getScale()
{
  return localScale;
}

void Transform::detachChildren()
{
  for(int i = 0; i < children->size(); i++)
  {
    Transform* child = children->at(i);
    child->setParent(NULL);
    // Dont just detach.. destroy
    Object::destroy(child->getGameObject());
  }

  children->clear();
}

Transform* Transform::find(std::string name)
{
  for(int i = 0; i < children->size(); i++)
  {
    if(children->at(i)->getGameObject()->getName() == name)
    {
      return children->at(i);
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
    for(int i = 0; i < this->parent->children->size(); i++)
    {
      if(this->parent->children->at(i) == this)
      {
        this->parent->children->remove_at(i);
        break;
      }
    }
  }

  if(transform != NULL)
  {
    transform->children->push_back(this);
  }

  setLocalPosition(getPosition());
  setLocalRotation(getRotation());
  this->parent = transform;
  setPosition(getLocalPosition());
  setRotation(getLocalRotation());
}

int Transform::getChildCount()
{
  return children->size();
}

Transform* Transform::getChild(int index)
{
  return children->at(index);
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

void Transform::rotateAround(Vector3 center, Vector3 axis, float amount)
{
  Matrix4x4 pos = Matrix4x4::getTrs(center,
                                    Vector3(0, 0, 0), Vector3(1, 1, 1));

  Matrix4x4 rot = Matrix4x4::getTrs(Vector3(0, 0, 0),
                                    Vector3(axis * amount), Vector3(1, 1, 1));

  Matrix4x4 curr = Matrix4x4::getIdentity();
  curr = curr * pos;
  curr = curr * rot;
  curr = curr * pos.inverse();

  localPosition = curr * localPosition;
}

Vector3 Transform::getForward()
{
  Matrix4x4 m = Matrix4x4::getTrs(localPosition, localRotation, Vector3(1, 1, 1));

  return m.multiplyVector(Vector3(0, 0, 1));  
}

Vector3 Transform::getRight()
{
  Matrix4x4 m = Matrix4x4::getTrs(localPosition, localRotation, Vector3(1, 1, 1));

  return m.multiplyVector(Vector3(1, 0, 0));  
}

}

}

