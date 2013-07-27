#include "Input.h"
#include "Vector3.h"

#include <SDL/SDL.h>

#include <string>

namespace mutiny
{

namespace engine
{

std::vector<int> Input::keys;
std::vector<int> Input::downKeys;
std::vector<int> Input::upKeys;
std::vector<int> Input::mouseButtons;
std::vector<int> Input::downMouseButtons;
std::vector<int> Input::upMouseButtons;
Vector3 Input::mousePosition;
Vector3 Input::mouseDownPosition;

Vector3 Input::getMousePosition()
{
  return mousePosition;
}

bool Input::getKey(int keyCode)
{
  for(int i = 0; i < keys.size(); i++)
  {
    if(keys.at(i) == keyCode)
    {
      return true;
    }
  }

  return false;
}

bool Input::getKeyUp(int keyCode)
{
  for(int i = 0; i < upKeys.size(); i++)
  {
    if(upKeys.at(i) == keyCode)
    {
      return true;
    }
  }

  return false;
}

bool Input::getKeyDown(int keyCode)
{
  for(int i = 0; i < downKeys.size(); i++)
  {
    if(downKeys.at(i) == keyCode)
    {
      return true;
    }
  }

  return false;
}

bool Input::getMouseButtonDown(int button)
{
  int sdlButton = translateButton(button);

  for(int i = 0; i < downMouseButtons.size(); i++)
  {
    if(downMouseButtons.at(i) == sdlButton)
    {
      return true;
    }
  }

  return false;
}

bool Input::getMouseButtonUp(int button)
{
  int sdlButton = translateButton(button);

  for(int i = 0; i < upMouseButtons.size(); i++)
  {
    if(upMouseButtons.at(i) == sdlButton)
    {
      return true;
    }
  }

  return false;
}

bool Input::getMouseButton(int button)
{
  int sdlButton = translateButton(button);

  for(int i = 0; i < mouseButtons.size(); i++)
  {
    if(mouseButtons.at(i) == sdlButton)
    {
      return true;
    }
  }

  return false;
}

int Input::translateButton(int input)
{
  if(input == 0)
  {
    return SDL_BUTTON_LEFT;
  }
  else if(input == 1)
  {
    return SDL_BUTTON_RIGHT;
  }
  //else if(input == 2)
  else
  {
    return SDL_BUTTON_MIDDLE;
  }
}

}

}

