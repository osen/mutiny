#include "Transform.h"
#include "Vector2.h"
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
  Debug::log("Transform awake");
  parent = NULL;
}

void Transform::setRotation(Vector3 rotation)
{
  localRotation = rotation;
}

void Transform::setPosition(Vector3 position)
{
  // Take off parent's existing position. Use setLocalPosition to set directly.
  localPosition = position;
}

Vector3 Transform::getPosition()
{
  return localPosition;
}

Vector3 Transform::getRotation()
{
  return localRotation;
}

Transform* Transform::getParent()
{
  return parent;
}

void Transform::setParent(Transform* transform)
{
  this->parent = transform;
}

Transform* Transform::getRoot()
{
  Transform* trans = parent;

  while(trans != NULL)
  {
    trans = trans->getParent();
  }

  return trans;
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

}

}

