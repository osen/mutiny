#include "Camera.h"
#include "Debug.h"
#include "GameObject.h"
#include "Matrix4x4.h"
#include "Screen.h"

namespace mutiny
{

namespace engine
{

ref<Camera> Camera::getMain()
{
  return Application::context->_main;
}

ref<Camera> Camera::getCurrent()
{
  return Application::context->current;
}

std::vector<ref<Camera> >& Camera::getAllCameras()
{
  return Application::context->allCameras;
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
  if(projectionMatrix != NULL)
  {
    return *projectionMatrix;
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
  this->projectionMatrix = new Matrix4x4();
  *this->projectionMatrix = projectionMatrix;
}

void Camera::resetProjectionMatrix()
{
  projectionMatrix = NULL;
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

void Camera::setTargetTexture(ref<RenderTexture> targetTexture)
{
  this->targetTexture = targetTexture;
}

void Camera::onStart()
{
  if(Application::context->_main.expired() &&
    getGameObject()->getName() == "MainCamera")
  {
    //Debug::log("MainCamera added");
    Application::context->_main = this;
  }

  Application::context->allCameras.push_back(this);
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

  if(Application::context->_main.try_get() == this)
  {
    Application::context->_main = NULL;
  }

  for(int i = 0; i < Application::context->allCameras.size(); i++)
  {
    if(Application::context->allCameras.at(i).get() == this)
    {
      Application::context->allCameras.erase(
        Application::context->allCameras.begin() + i);

      i--;
    }
  }
}

}

}

