#ifndef MUTINY_ENGINE_MATRIX4X4_H
#define MUTINY_ENGINE_MATRIX4X4_H

#include "glm/glm.hpp"

namespace mutiny
{

namespace engine
{

class Material;
class Gui;
class Vector3;

class Matrix4x4
{
  friend class mutiny::engine::Material;
  friend class mutiny::engine::Gui;

public:
  static Matrix4x4 ortho(float left, float right, float bottom, float top,
               float zNear, float zFar);

  static Matrix4x4 perspective(float fov, float aspect,
                               float zNear, float zFar);

  static Matrix4x4 getIdentity();
  static Matrix4x4 getZero();
  static Matrix4x4 getTrs(Vector3 position, Vector3 rotation, Vector3 scale);

  Matrix4x4 translate(Vector3 vector);
  Matrix4x4 rotate(Vector3 vector);
  Matrix4x4 rotate(float angle, Vector3 vector);
  Matrix4x4 inverse();

  Vector3 multiplyPoint(Vector3 v);
  Vector3 multiplyVector(Vector3 v);

  Vector3 operator*(Vector3 param);
  Matrix4x4 operator*(Matrix4x4 param);

private:
  float m[16];
  glm::mat4 mat;

  Matrix4x4();
  float* getValue();

};

}

}

#endif

