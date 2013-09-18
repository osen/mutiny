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

class Application
{
  friend class mutiny::engine::Resources;
  friend class mutiny::engine::GameObject;
  friend class mutiny::engine::CharacterController;

public:
  static void quit();
  static void loadLevel(std::string path);
  static std::string getLoadedLevelName();
  static std::string getDataPath();
  static int getArgc();
  static std::string getArgv(int i);

  Application(int argc, char* argv[]);
  void run();

private:
  static Application* instance;

  static void loadLevel();
  static void loop();
  static void displaySplash();

  std::shared_ptr<SDL_Surface> screen;
  bool running;
  bool initialized;
  std::string loadedLevelName;
  std::vector<std::shared_ptr<GameObject> > gameObjects;
  std::string levelChange;
  std::string dataPath;
  std::string engineDataPath;

  int argc;
  std::vector<std::string> argv;

  void setupPaths();

};

}

}

#endif

