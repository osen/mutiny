#ifndef MUTINY_ENGINE_OBJECT_H
#define MUTINY_ENGINE_OBJECT_H

#include "arc.h"

#include <string>

namespace mutiny
{

namespace engine
{

class Application;
class GameObject;

class Object
{
  friend class Application;
  friend class GameObject;

public:
  static void dontDestroyOnLoad(arc<Object> object);
  static void dontDestroyOnLoad(Object* object);
  static void destroy(Object* object);

  Object();
  virtual ~Object();

  void setName(std::string name);
  std::string getName();

private:
  std::string name;
  bool destroyOnLoad;
  bool destroyed;

};

}

}

#endif

