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
  static void init(int argc, char* argv[]);
  static void run();
  static void quit();
  static void loadLevel(std::string path);
  static std::string getLoadedLevelName();
  static std::string getDataPath();

private:
  static std::shared_ptr<SDL_Surface> screen;
  static bool running;
  static bool initialized;
  static std::string loadedLevelName;
  static std::vector<std::shared_ptr<GameObject> > gameObjects;
  static std::string levelChange;
  static std::string dataPath;
  static std::string engineDataPath;

  static void loadLevel();
  static void loop();

};

}

}

#endif

