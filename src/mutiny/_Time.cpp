#include "_Time.h"

namespace mutiny
{

namespace engine
{

float Time::deltaTime = 0;

float Time::getDeltaTime()
{
  if(deltaTime > 0.05f)
  {
    return 0.05f;
  }

  return deltaTime;
}

}

}

