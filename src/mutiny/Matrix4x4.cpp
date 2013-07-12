#include "Matrix4x4.h"
#include "Vector3.h"

#include "glm/glm.hpp"
#include "glm/ext.hpp"

#include <cmath>

namespace mutiny
{

namespace engine
{

Matrix4x4 Matrix4x4::ortho(float left, float right, float bottom, float top,
                           float zNear, float zFar)
{
  Matrix4x4 mat;

  mat.mat = glm::ortho(left, right, bottom, top, zNear, zFar);

  return mat;
}

Matrix4x4 Matrix4x4::perspective(float fov, float aspect,
                                 float zNear, float zFar)
{
  Matrix4x4 mat;

  mat.mat = glm::perspective(fov, aspect, zNear, zFar);

  return mat;
}

Matrix4x4 Matrix4x4::getTrs(Vector3 position, Vector3 rotation, Vector3 scale)
{
  Matrix4x4 mat = getIdentity();

  mat.mat = glm::translate(mat.mat, glm::vec3(position.x,
                                              position.y,
                                              position.z));

  mat.mat = glm::rotate(mat.mat, rotation.y, glm::vec3(0, 1, 0));
  mat.mat = glm::rotate(mat.mat, rotation.x, glm::vec3(1, 0, 0));
  mat.mat = glm::rotate(mat.mat, rotation.z, glm::vec3(0, 0, 1));

  mat.mat = glm::scale(mat.mat, glm::vec3(scale.x, scale.y, scale.z));

  return mat;
}

Matrix4x4::Matrix4x4()
{

}

Matrix4x4 Matrix4x4::getIdentity()
{
  Matrix4x4 mat;

  mat.mat = glm::mat4(1.0f);

  return mat;
}

Matrix4x4 Matrix4x4::getZero()
{
  Matrix4x4 mat;

  mat.mat = glm::mat4(0.0f);

  return mat;
}

Matrix4x4 Matrix4x4::rotate(Vector3 vector)
{
  Matrix4x4 mat = rotate(vector.z, Vector3(0, 0, 1));
            mat = mat.rotate(vector.x, Vector3(1, 0, 0));
            mat = mat.rotate(vector.y, Vector3(0, 1, 0));

  return mat;
}

float* Matrix4x4::getValue()
{
  return glm::value_ptr(mat);
}

Matrix4x4 Matrix4x4::translate(Vector3 vector)
{
  Matrix4x4 mat;

  mat.mat = glm::translate(this->mat, glm::vec3(vector.x, vector.y, vector.z));

  return mat;
}

Matrix4x4 Matrix4x4::rotate(float angle, Vector3 vector)
{
  Matrix4x4 mat;

  mat.mat = glm::rotate(this->mat, angle, glm::vec3(vector.x, vector.y, vector.z));

  return mat;
}

Matrix4x4 Matrix4x4::inverse()
{
  Matrix4x4 mat;

  mat.mat = glm::inverse(this->mat);

  return mat;
}

Vector3 Matrix4x4::multiplyPoint(Vector3 v)
{
  glm::vec4 rtn = mat * glm::vec4(v.x, v.y, v.z, 1.0f);

  return Vector3(rtn.x, rtn.y, rtn.z);
}

Vector3 Matrix4x4::operator*(Vector3 param)
{
  glm::vec4 rtn = mat * glm::vec4(param.x, param.y, param.z, 1.0f);

  return Vector3(rtn.x, rtn.y, rtn.z);
}

Matrix4x4 Matrix4x4::operator*(Matrix4x4 param)
{
  Matrix4x4 mat;

  mat.mat = this->mat * param.mat;

  return mat;
}

}

}

