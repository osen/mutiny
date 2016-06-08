#ifndef MUTINY_ENGINE_OBJECT_H
#define MUTINY_ENGINE_OBJECT_H

#include "ref.h"

#include <string>

namespace mutiny
{

namespace engine
{

class Application;
class GameObject;

class Object : public enable_ref
{
  friend class Application;
  friend class GameObject;

public:
  static void dontDestroyOnLoad(ref<Object> object);
  static void dontDestroyOnLoad(ref<GameObject> object);
  static void destroy(ref<Object> object);
  static void destroy(ref<GameObject> object);

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

