#include "Object.h"

namespace mutiny
{

namespace engine
{

void Object::dontDestroyOnLoad(arc<Object> object)
{
  object->destroyOnLoad = false;
}

void Object::dontDestroyOnLoad(Object* object)
{
  object->destroyOnLoad = false;
}

void Object::destroy(Object* object)
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

