#ifndef MUTINY_ENGINE_APPLICATION_H
#define MUTINY_ENGINE_APPLICATION_H

#include "internal/platform.h"
#include "arc.h"

#ifdef USE_SDL
  #include <SDL/SDL.h>
#endif

#include <memory>
#include <vector>
#include <string>

namespace mutiny
{

namespace engine
{

class GameObject;
class CharacterController;
class Resources;
class Camera;
class Gui;
class Graphics;
class Material;
class RenderTexture;
class Screen;

class Application
{
  friend class mutiny::engine::Resources;
  friend class mutiny::engine::GameObject;
  friend class mutiny::engine::CharacterController;
  friend class mutiny::engine::Camera;
  friend class mutiny::engine::Gui;
  friend class mutiny::engine::Graphics;
  friend class mutiny::engine::Material;
  friend class mutiny::engine::RenderTexture;
  friend class mutiny::engine::Screen;

public:
  static void init(int argc, char* argv[]);
  static void destroy();
  static void run();
  static void quit();
  static void loadLevel(std::string path);
  static std::string getLoadedLevelName();
  static std::string getDataPath();
  static int getArgc();
  static std::string getArgv(int i);
  static void setTitle(std::string title);

private:
#ifdef USE_SDL
  static SDL_Surface* screen;
#endif
  static bool running;
  static std::string loadedLevelName;
  static std::string levelChange;
  static std::string dataPath;
  static std::string engineDataPath;
  static std::vector<arc<GameObject> > gameObjects;

  static int argc;
  static std::vector<std::string> argv;

  static void loadLevel();
  static void loop();
  static void setupPaths();
  static bool isValidPrefix(std::string path, std::string basename);

  static void reshape(int width, int height);
  static void display();
  static void idle();
  static void motion(int x, int y);
  static void mouse(int button, int state, int x, int y);
  static void keyboard(unsigned char key, int x, int y);
  static void keyboardUp(unsigned char key, int x, int y);

  static void _keyboard(int key, int x, int y);
  static void _keyboardUp(int key, int x, int y);

};

}

}

#endif

