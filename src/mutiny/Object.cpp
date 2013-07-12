#include "Object.h"

namespace mutiny
{

namespace engine
{

void Object::dontDestroyOnLoad(Object* object)
{
  object->destroyOnLoad = false;
}

Object::Object()
{
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

