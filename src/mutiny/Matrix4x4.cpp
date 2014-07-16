#include "Matrix4x4.h"
#include "Vector3.h"
#include "Mathf.h"

#include "internal/linmath.h"

namespace mutiny
{

namespace engine
{

Matrix4x4 Matrix4x4::ortho(float left, float right, float bottom, float top,
                           float zNear, float zFar)
{
  Matrix4x4 mat;

  mat4x4_ortho(mat.m, left, right, bottom, top, zNear, zFar);

  return mat;
}

Matrix4x4 Matrix4x4::perspective(float fov, float aspect,
                                 float zNear, float zFar)
{
  Matrix4x4 mat;

  mat4x4_perspective(mat.m, Mathf::deg2Rad(fov), aspect, zNear, zFar);

  return mat;
}

Matrix4x4 Matrix4x4::getTrs(Vector3 position, Vector3 rotation, Vector3 scale)
{
  mat4x4 tmpMat;
  Matrix4x4 mat = getIdentity();

  mat4x4_translate(mat.m, position.x, position.y, position.z);

  mat4x4_rotate(tmpMat, mat.m, 0, 1, 0, Mathf::deg2Rad(rotation.y));
  mat4x4_rotate(mat.m, tmpMat, 0, 0, 1, Mathf::deg2Rad(rotation.z));
  mat4x4_rotate(tmpMat, mat.m, 1, 0, 0, Mathf::deg2Rad(rotation.x));

  // Todo: scale
  mat4x4_scale_aniso(mat.m, tmpMat, scale.x, scale.y, scale.z);

  return mat;
}

Matrix4x4::Matrix4x4()
{
  mat4x4_identity(m);
}

Matrix4x4 Matrix4x4::getIdentity()
{
  Matrix4x4 mat;

  mat4x4_identity(mat.m);

  return mat;
}

Matrix4x4 Matrix4x4::getZero()
{
  Matrix4x4 mat;

  // TODO: set to zero rather than identity
  mat4x4_identity(mat.m);

  return mat;
}

Matrix4x4 Matrix4x4::rotate(Vector3 vector)
{
  mat4x4 tmpMat;

  Matrix4x4 mat = rotate(vector.z, Vector3(0, 0, 1));
            mat = mat.rotate(vector.x, Vector3(1, 0, 0));
            mat = mat.rotate(vector.y, Vector3(0, 1, 0));

  mat4x4_identity(tmpMat);
  mat4x4_rotate(mat.m, tmpMat, 0, 0, 1, Mathf::deg2Rad(vector.z));
  mat4x4_rotate(tmpMat, mat.m, 0, 1, 0, Mathf::deg2Rad(vector.y));
  mat4x4_rotate(mat.m, tmpMat, 1, 0, 0, Mathf::deg2Rad(vector.x));

  return mat;
}

float* Matrix4x4::getValue()
{
  return (float*)m;
}

Matrix4x4 Matrix4x4::translate(Vector3 vector)
{
  Matrix4x4 mat;

  mat4x4_translate_in_place(mat.m, vector.x, vector.y, vector.z);

  return mat;
}

Matrix4x4 Matrix4x4::rotate(float angle, Vector3 vector)
{
  mat4x4 tmpMat;
  Matrix4x4 mat;

  mat4x4_identity(tmpMat);
  mat4x4_rotate(mat.m, tmpMat, vector.x, vector.y, vector.z, angle);

  return mat;
}

Matrix4x4 Matrix4x4::inverse()
{
  Matrix4x4 mat;

  mat4x4_invert(mat.m, m);

  return mat;
}

Matrix4x4 Matrix4x4::transpose()
{
  Matrix4x4 mat;

  mat4x4_transpose(mat.m, m);

  return mat;
}

Vector3 Matrix4x4::multiplyPoint(Vector3 v)
{
  vec4 rtnVec;
  vec4 tmpVec;

  tmpVec[0] = v.x;
  tmpVec[1] = v.y;
  tmpVec[2] = v.z;
  tmpVec[3] = 1.0f;
  mat4x4_mul_vec4(rtnVec, m, tmpVec);

  return Vector3(rtnVec[0], rtnVec[1], rtnVec[2]);
}

Vector3 Matrix4x4::multiplyVector(Vector3 v)
{
  vec4 rtnVec;
  vec4 tmpVec;

  tmpVec[0] = v.x;
  tmpVec[1] = v.y;
  tmpVec[2] = v.z;
  tmpVec[3] = 0.0f;
  mat4x4_mul_vec4(rtnVec, m, tmpVec);

  return Vector3(rtnVec[0], rtnVec[1], rtnVec[2]);
}

Vector3 Matrix4x4::operator*(Vector3 param)
{
  vec4 rtnVec;
  vec4 tmpVec;

  tmpVec[0] = param.x;
  tmpVec[1] = param.y;
  tmpVec[2] = param.z;
  tmpVec[3] = 1.0f;
  mat4x4_mul_vec4(rtnVec, m, tmpVec);

  return Vector3(rtnVec[0], rtnVec[1], rtnVec[2]);
}

Matrix4x4 Matrix4x4::operator*(Matrix4x4 param)
{
  Matrix4x4 mat;

  mat4x4_mul(mat.m, m, param.m);

  return mat;
}

}

}

