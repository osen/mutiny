#ifndef INSPECTORCAMERA_H
#define INSPECTORCAMERA_H

#include <mutiny/mutiny.h>

using namespace mutiny::engine;

class InspectorCamera : public Behaviour
{
public:
  static InspectorCamera* create();

  virtual void onAwake();

  RenderTexture* getRenderTexture();

private:
  std::shared_ptr<RenderTexture> rt;

};

#endif

