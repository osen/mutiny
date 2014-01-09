#ifndef MUTINY_ENGINE_CAMERA_H
#define MUTINY_ENGINE_CAMERA_H

#include "Behaviour.h"
#include "Matrix4x4.h"

#include <memory>

#include <vector>

namespace mutiny
{

namespace engine
{

class Application;
class RenderTexture;

class Camera : public Behaviour
{
  friend class mutiny::engine::Application;

public:
  static Camera* getMain();
  static Camera* getCurrent();
  static std::vector<Camera*>* getAllCameras();

  virtual ~Camera();

  Matrix4x4 getProjectionMatrix();
  void setProjectionMatrix(Matrix4x4 projectionMatrix);
  void resetProjectionMatrix();
  void setTargetTexture(RenderTexture* texture);

private:
  float fieldOfView;
  bool orthographic;
  float orthographicSize;
  float nearClipPlane;
  float farClipPlane;
  std::shared_ptr<Matrix4x4> projectionMatrix;
  RenderTexture* targetTexture;

  virtual void onAwake();
  virtual void onStart();
  virtual void onDestroy();

};

}

}

#endif

