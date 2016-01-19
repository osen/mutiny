#ifndef MUTINY_ENGINE_TRANSFORM_H
#define MUTINY_ENGINE_TRANSFORM_H

#include "Behaviour.h"
#include "Vector3.h"

#include <vector>

namespace mutiny
{

namespace engine
{

class Transform : public Behaviour
{
public:
  virtual ~Transform();

  Vector3 getPosition();
  Vector3 getRotation();
  Vector3 getScale();
  void setPosition(Vector3 position);
  void setRotation(Vector3 rotation);
  void setScale(Vector3 scale);

  Vector3 getLocalPosition();
  Vector3 getLocalRotation();
  void setLocalPosition(Vector3 position);
  void setLocalRotation(Vector3 rotation);
  void setLocalScale(Vector3 scale);

  void detachChildren();
  Transform* getParent();
  void setParent(Transform* transform);
  int getChildCount();
  Transform* getChild(int index);
  Transform* getRoot();
  Transform* find(std::string name);

  void rotate(Vector3 eulerAngles);
  void translate(Vector3 translation);
  void lookAt(Vector3 worldPosition);
  void rotateAround(Vector3 center, Vector3 axis, float amount);

  Vector3 getForward();
  Vector3 getRight();

private:
  Vector3 localPosition;
  Vector3 localRotation;
  Vector3 localScale;
  Transform* parent;
  std::vector<Transform*> children;

  virtual void onAwake();
  virtual void onDestroy();

};

}

}

#endif

