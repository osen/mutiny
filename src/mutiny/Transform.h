#ifndef MUTINY_ENGINE_TRANSFORM_H
#define MUTINY_ENGINE_TRANSFORM_H

#include "Behaviour.h"
#include "Vector3.h"

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
  void setPosition(Vector3 position);
  void setRotation(Vector3 rotation);
  Transform* getParent();
  void setParent(Transform* transform);
  Transform* getRoot();

  void rotate(Vector3 eulerAngles);
  void translate(Vector3 translation);
  void lookAt(Vector3 worldPosition);
  void rotateAround(Vector3 center, Vector3 axis, float amount);

private:
  Vector3 localPosition;
  Vector3 localRotation;
  Transform* parent;

  virtual void onAwake();

};

}

}

#endif

