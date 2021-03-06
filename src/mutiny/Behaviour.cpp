#include "Behaviour.h"
#include "Debug.h"

namespace mutiny
{

namespace engine
{

Behaviour::~Behaviour()
{

}

void Behaviour::awake()
{
  started = false;
  onAwake();
}

void Behaviour::update()
{
  if(started == false)
  {
    onStart();
    started = true;
  }

  onUpdate();
}

void Behaviour::postRender()
{
  if(started == false)
  {
    return;
  }

  onPostRender();
}

void Behaviour::gui()
{
  if(started == false)
  {
    return;
  }

  onGui();
}

void Behaviour::destroy()
{
  onDestroy();
}

void Behaviour::levelWasLoaded()
{
  onLevelWasLoaded();
}

void Behaviour::onAwake()
{

}

void Behaviour::onStart()
{

}

void Behaviour::onUpdate()
{

}

void Behaviour::onPostRender()
{

}

void Behaviour::onGui()
{

}

void Behaviour::onDestroy()
{

}

void Behaviour::onLevelWasLoaded()
{

}

}

}

