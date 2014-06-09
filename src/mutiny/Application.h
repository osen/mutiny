#ifndef MUTINY_ENGINE_APPLICATION_H
#define MUTINY_ENGINE_APPLICATION_H

#include <SDL/SDL.h>

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
  static void loadLevelAdditive(std::string path);
  static std::string getLoadedLevelName();
  static std::string getDataPath();
  static int getArgc();
  static std::string getArgv(int i);

private:
  static SDL_Surface* screen;
  static bool running;
  static std::string loadedLevelName;
  static std::string levelChange;
  static std::string dataPath;
  static std::string engineDataPath;
  static std::vector<std::shared_ptr<GameObject> > gameObjects;

  static int argc;
  static std::vector<std::string> argv;

  static void loadLevel();
  static void loop();
  static void displaySplash();
  static void setupPaths();

  static void reshape(int width, int height);
  static void display();
  static void idle();
  static void motion(int x, int y);
  static void mouse(int button, int state, int x, int y);
  static void keyboard(int key, int x, int y);
  static void keyboardUp(int key, int x, int y);

};

}

}

#endif

