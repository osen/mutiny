#include "Camera.h"
#include "Debug.h"
#include "GameObject.h"
#include "Matrix4x4.h"
#include "Screen.h"

namespace mutiny
{

namespace engine
{

std::vector<Camera*> Camera::allCameras;
Camera* Camera::current;
Camera* Camera::_main;

Camera* Camera::getMain()
{
  return Camera::_main;
}

Camera* Camera::getCurrent()
{
  return current;
}

std::vector<Camera*>* Camera::getAllCameras()
{
  return &allCameras;
}

Camera::~Camera()
{

}

//Matrix4x4 Camera::getWorldToCameraMatrix()
//{
//
//}

Matrix4x4 Camera::getProjectionMatrix()
{
  if(projectionMatrix.get() != NULL)
  {
    return *projectionMatrix.get();
  }

  if(orthographic == true)
  {
    return Matrix4x4::ortho(0, Screen::getWidth(), Screen::getHeight(), 0, -1, 1);
  }
  else
  {
    return Matrix4x4::perspective(fieldOfView, (float)Screen::getWidth() / (float)Screen::getHeight(), nearClipPlane, farClipPlane);
  }
}

void Camera::setProjectionMatrix(Matrix4x4 projectionMatrix)
{
  this->projectionMatrix.reset(new Matrix4x4(projectionMatrix));
}

void Camera::resetProjectionMatrix()
{
  projectionMatrix.reset();
}

void Camera::onAwake()
{
  orthographic = false;
  fieldOfView = 60.0f;
  orthographicSize = 100;
  nearClipPlane = 0.3f;
  farClipPlane = 1000.0f;
  cullMask = 1 << 0;

  backgroundColor = Color(49.0f / 255.0f, 77.0f / 255.0f, 121.0f / 255.0f, 1.0f);
}

void Camera::setCullMask(int cullMask)
{
  this->cullMask = cullMask;
}

int Camera::getCullMask()
{
  return cullMask;
}

void Camera::setTargetTexture(arc<RenderTexture> targetTexture)
{
  this->targetTexture = targetTexture;
}

void Camera::onStart()
{
  if(_main == NULL && getGameObject()->getName() == "MainCamera")
  {
    //Debug::log("MainCamera added");
    _main = this;
  }

  allCameras.push_back(this);
}

Color Camera::getBackgroundColor()
{
  return backgroundColor;
}

void Camera::setBackgroundColor(Color color)
{
  this->backgroundColor = color;
}

void Camera::onDestroy()
{
  //Debug::log("Camera destroyed");

  if(_main == this)
  {
    _main = NULL;
  }

  for(int i = 0; i < allCameras.size(); i++)
  {
    if(allCameras.at(i) == this)
    {
      allCameras.erase(allCameras.begin() + i);
      i--;
    }
  }
}

}

}

