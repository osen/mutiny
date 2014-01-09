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
  std::shared_ptr<SDL_Surface> screen;
  bool running;
  bool initialized;
  std::string loadedLevelName;
  std::string levelChange;
  std::string dataPath;
  std::string engineDataPath;
  std::vector<std::shared_ptr<GameObject> > gameObjects;

  int argc;
  std::vector<std::string> argv;

  // Camera
  Camera* mainCamera;
  Camera* currentCamera;
  std::vector<Camera*> allCameras;

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
