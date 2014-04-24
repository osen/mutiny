#ifndef MUTINY_ENGINE_INTERNAL_INTERNAL_H
#define MUTINY_ENGINE_INTERNAL_INTERNAL_H

#include <SDL/SDL.h>

#include <string>
#include <vector>
#include <memory>

namespace mutiny
{

namespace engine
{

class GameObject;
class Camera;
class GuiSkin;
class Material;
class RenderTexture;

namespace internal
{

class Internal
{
public:
  // Gui
  GuiSkin* skin;

  // GuiSkin
  std::shared_ptr<GuiSkin> defaultGuiSkin;

  Material* currentMaterial;

  // Graphics
  Material* graphicsDefaultMaterial;
  RenderTexture* graphicsRenderTarget;

  Internal();

};

}

}

}

#endif
