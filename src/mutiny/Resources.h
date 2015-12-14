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
  template<class T> static arc<T> load(std::string path)
  {
    std::stringstream ss;
    ss << path << "_" << typeid(T).name();

    for(int i = 0; i < paths.size(); i++)
    {
      if(ss.str() == paths.at(i))
      {
        return objects.at(i).dynamicCast<T>();
      }
    }

    T* t = NULL;

    // Game specific resources
    try
    {
      t = T::load(Application::dataPath + "/" + path);
    }
    catch(std::exception& e){}

    // Internal engine files
    if(t == NULL)
    {
      try
      {
        t = T::load(Application::engineDataPath + "/" + path);
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

    arc<Object> rtn;

    if(t == NULL)
    {
      //Debug::logError("Failed to load '" + path + "'");
      return rtn.dynamicCast<T>();
    }

    rtn.reset(t);

    paths.push_back(ss.str());
    objects.push_back(rtn);

    return rtn.dynamicCast<T>();
  }

private:
  static std::vector<std::string> paths;
  static std::vector<arc<Object> > objects;

};

}

}

#endif

