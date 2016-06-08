#include "Object.h"
#include "GameObject.h"

namespace mutiny
{

namespace engine
{

void Object::dontDestroyOnLoad(ref<Object> object)
{
  object->destroyOnLoad = false;
}

void Object::dontDestroyOnLoad(ref<GameObject> object)
{
  object->destroyOnLoad = false;
}

void Object::destroy(ref<Object> object)
{
  object->destroyed = true;
}

void Object::destroy(ref<GameObject> object)
{
  object->destroyed = true;
}

Object::Object()
{
  destroyed = false;
  destroyOnLoad = true;
}

Object::~Object()
{

}

std::string Object::getName()
{
  return name;
}

void Object::setName(std::string name)
{
  this->name = name;
}

}

}

