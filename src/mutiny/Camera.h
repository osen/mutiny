#ifndef MUTINY_ENGINE_CAMERA_H
#define MUTINY_ENGINE_CAMERA_H

#include "Behaviour.h"
#include "Matrix4x4.h"
#include "Color.h"

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
  //Matrix4x4 getWorldToCameraMatrix();
  void setProjectionMatrix(Matrix4x4 projectionMatrix);
  void resetProjectionMatrix();
  void setTargetTexture(RenderTexture* texture);
  void setBackgroundColor(Color color);
  Color getBackgroundColor();
  int getCullMask();
  void setCullMask(int cullMask);

private:
  Color backgroundColor;
  float fieldOfView;
  bool orthographic;
  float orthographicSize;
  float nearClipPlane;
  float farClipPlane;
  std::shared_ptr<Matrix4x4> projectionMatrix;
  RenderTexture* targetTexture;
  int cullMask;

  virtual void onAwake();
  virtual void onStart();
  virtual void onDestroy();

};

}

}

#endif

