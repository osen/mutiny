#ifndef MUTINY_ENGINE_APPLICATION_H
#define MUTINY_ENGINE_APPLICATION_H

#include "internal/Internal.h"

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
  static void destroy();
  static void run();
  static void quit();
  static void loadLevel(std::string path);
  static std::string getLoadedLevelName();
  static std::string getDataPath();
  static int getArgc();
  static std::string getArgv(int i);

private:
  static std::shared_ptr<internal::Internal> _internal;

  static void loadLevel();
  static void loop();
  static void displaySplash();
  static void setupPaths();

  static internal::Internal* getInternal();

};

}

}

#endif

