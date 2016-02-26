#ifndef MUTINY_ENGINE_RESOURCES_H
#define MUTINY_ENGINE_RESOURCES_H

#include "Debug.h"
#include "Material.h"
#include "Application.h"
#include "Object.h"

#include <memory>
#include <string>
#include <vector>
#include <typeinfo>
#include <sstream>
#include <iostream>

namespace mutiny
{

namespace engine
{

class Object;
class Application;

class Resources
{
  friend class mutiny::engine::Application;

public:
  template<class T> static T* load(std::string path)
  {
    std::stringstream ss;
    ss << path << "_" << typeid(T).name();

    for(size_t i = 0; i < Application::context->paths.size(); i++)
    {
      if(ss.str() == Application::context->paths.at(i))
      {
        return dynamic_cast<T*>(Application::context->objects->at(i));
      }
    }

    T* t = NULL;

    // Game specific resources
    try
    {
      t = T::load(Application::getDataPath() + "/" + path);
    }
    catch(std::exception& e){}

    // Internal engine files
    if(t == NULL)
    {
      try
      {
        t = T::load(Application::getEngineDataPath() + "/" + path);
      }
      catch(std::exception& e){}
    }

    // Absolute path
    if(t == NULL)
    {
      try
      {
        t = T::load(path);
      }
      catch(std::exception& e){}
    }

    if(t == NULL)
    {
      std::cout << "Loading: " << path << "... Failed" << std::endl;
      //Debug::logError("Failed to load '" + path + "'");
      return NULL;
    }

    Application::context->paths.push_back(ss.str());
    Application::context->objects->push_back(t);

    std::cout << "Loading: " << path << "... Success" << std::endl;
    return t;
  }

};

}

}

#endif

