#ifndef MUTINY_ENGINE_TIME_H
#define MUTINY_ENGINE_TIME_H

namespace mutiny
{

namespace engine
{

class Application;
class Time
{
  friend class mutiny::engine::Application;

public:
  static float getDeltaTime();

private:
  static float deltaTime;

};

}

}

#endif

