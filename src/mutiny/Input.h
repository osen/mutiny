#ifndef MUTINY_ENGINE_INPUT_H
#define MUTINY_ENGINE_INPUT_H

#include "Vector3.h"

#include <string>
#include <vector>

namespace mutiny
{

namespace engine
{

class Application;

class Input
{
  friend class mutiny::engine::Application;

public:
  static bool getKey(int keyCode);
  static bool getKeyDown(int keyCode);
  static bool getKeyUp(int keyCode);
  static Vector3 getMousePosition();
  static bool getMouseButton(int button);
  static bool getMouseButtonUp(int button);
  static bool getMouseButtonDown(int button);

private:
  static std::vector<int> keys;
  static std::vector<int> upKeys;
  static std::vector<int> downKeys;
  static std::vector<int> mouseButtons;
  static std::vector<int> upMouseButtons;
  static std::vector<int> downMouseButtons;
  static Vector3 mousePosition;
  static int translateButton(int input);

};

}

}

#endif

