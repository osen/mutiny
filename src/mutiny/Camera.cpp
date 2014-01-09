#include "Camera.h"
#include "Debug.h"
#include "GameObject.h"
#include "Matrix4x4.h"
#include "Screen.h"

namespace mutiny
{

namespace engine
{

Camera* Camera::getMain()
{
  return Application::getInternal()->mainCamera;
}

Camera* Camera::getCurrent()
{
  return Application::getInternal()->currentCamera;
}

std::vector<Camera*>* Camera::getAllCameras()
{
  return &Application::getInternal()->allCameras;
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
  targetTexture = NULL;
  nearClipPlane = 0.3f;
  farClipPlane = 1000.0f;
}

void Camera::setTargetTexture(RenderTexture* targetTexture)
{
  this->targetTexture = targetTexture;
}

void Camera::onStart()
{
  if(Application::getInternal()->mainCamera == NULL && getGameObject()->getName() == "MainCamera")
  {
    //Debug::log("MainCamera added");
    Application::getInternal()->mainCamera = this;
  }

  Application::getInternal()->allCameras.push_back(this);
}

void Camera::onDestroy()
{
  //Debug::log("Camera destroyed");

  if(Application::getInternal()->mainCamera == this)
  {
    Application::getInternal()->mainCamera = NULL;
  }

  for(int i = 0; i < Application::getInternal()->allCameras.size(); i++)
  {
    if(Application::getInternal()->allCameras.at(i) == this)
    {
      Application::getInternal()->allCameras.erase(Application::getInternal()->allCameras.begin() + i);
      i--;
    }
  }
}

}

}

