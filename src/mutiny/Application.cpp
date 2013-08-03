#include "Application.h"
#include "GameObject.h"
#include "Component.h"
#include "Camera.h"
#include "Material.h"
#include "Screen.h"
#include "Time.h"
#include "Input.h"
#include "RenderTexture.h"
#include "Resources.h"
#include "GuiSkin.h"
#include "Shader.h"
#include "Debug.h"

#include <GL/glew.h>
#include <SDL/SDL.h>

#ifdef EMSCRIPTEN
#include <emscripten.h>
#endif

#include <functional>
#include <iostream>

namespace mutiny
{

namespace engine
{

std::shared_ptr<SDL_Surface> Application::screen;
bool Application::initialized = false;
bool Application::running = false;
std::string Application::levelChange;
std::string Application::loadedLevelName;
std::vector<std::shared_ptr<GameObject> > Application::gameObjects;
std::string Application::dataPath;
std::string Application::engineDataPath;

void Application::init(int argc, char* argv[])
{
  if(initialized == true)
  {
    std::cout << "Error: Already initialized" << std::endl;
    throw std::exception();
  }

  if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
  {
    std::cout << "Error: Failed to initialize" << std::endl;
    throw std::exception();
  }

  screen.reset(SDL_SetVideoMode(800, 600, 32, SDL_OPENGL), std::bind(SDL_Quit));

  if(screen.get() == NULL)
  {
    std::cout << "Error: Failed to create rendering context" << std::endl;
    throw std::exception();
  }

  SDL_WM_SetCaption("Mutiny Engine", NULL);

  glewInit();
  //if(glewInit() != 0)
  //{
  //  std::cout << "Error: Failed to initialize OpenGL" << std::endl;
  //  throw std::exception();
  //}

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_FRONT);

  engineDataPath = "share/mutiny";
  dataPath = std::string("share/") + GAMENAME;

  Material::defaultMaterial = Resources::load<Material>("shaders/default_diffuse");
  Object::dontDestroyOnLoad(Material::defaultMaterial);

  Material::guiMaterial = Resources::load<Material>("shaders/default_gui");
  Object::dontDestroyOnLoad(Material::guiMaterial);

  Material::particleMaterial = Resources::load<Material>("shaders/default_particle");
  Object::dontDestroyOnLoad(Material::particleMaterial);

  GuiSkin::defaultGuiSkin.reset(new GuiSkin());

  initialized = true;
}

void Application::run()
{
  if(running == true)
  {
    std::cout << "Error: Already running" << std::endl;
    throw std::exception();
  }

  running = true;

#ifdef EMSCRIPTEN
  //loop();
  emscripten_set_main_loop(loop, 60, true);
#else
  while(running == true)
  {
    loop();
  }

  running = false;

  for(int i = 0; i < gameObjects.size(); i++)
  {
    gameObjects.at(i)->destroy();
  }
#endif
}

void Application::loop()
{
  SDL_Event event = { 0 };

  static float lastTime = SDL_GetTicks();
  float time = SDL_GetTicks();
  float diff = time - lastTime;
  Time::deltaTime = diff / 1000.0f;
  lastTime = time;

  Screen::width = screen->w;
  Screen::height = screen->h;

  Input::downKeys.clear();
  Input::upKeys.clear();
  Input::downMouseButtons.clear();
  Input::upMouseButtons.clear();

  while(SDL_PollEvent(&event))
  {
    if(event.type == SDL_QUIT)
    {
      running = false;
    }
    else if(event.type == SDL_MOUSEMOTION)
    {
      Input::mousePosition.x = event.motion.x;
      Input::mousePosition.y = event.motion.y;
    }
    else if(event.type == SDL_MOUSEBUTTONDOWN)
    {
      for(int i = 0; i < Input::mouseButtons.size(); i++)
      {
        if(Input::mouseButtons.at(i) == event.button.button)
        {
          continue;
        }
      }

      Input::mouseDownPosition.x = Input::mousePosition.x;
      Input::mouseDownPosition.y = Input::mousePosition.y;
      Input::mouseButtons.push_back(event.button.button);
      Input::downMouseButtons.push_back(event.button.button);
    }
    else if(event.type == SDL_MOUSEBUTTONUP)
    {
      for(int i = 0; i < Input::mouseButtons.size(); i++)
      {
        if(Input::mouseButtons.at(i) == event.button.button)
        {
          Input::mouseButtons.erase(Input::mouseButtons.begin() + i);
          i--;
        }
      }

      Input::upMouseButtons.push_back(event.button.button);
      //std::cout << (int)event.button.button << std::endl;
    }
    else if(event.type == SDL_KEYDOWN)
    {
      //std::cout << event.key.keysym.sym << std::endl;
      for(int i = 0; i < Input::keys.size(); i++)
      {
        if(Input::keys.at(i) == event.key.keysym.sym)
        {
          continue;
        }
      }

      Input::keys.push_back(event.key.keysym.sym);
      Input::downKeys.push_back(event.key.keysym.sym);
    }
    else if(event.type == SDL_KEYUP)
    {
      for(int i = 0; i < Input::keys.size(); i++)
      {
        if(Input::keys.at(i) == event.key.keysym.sym)
        {
          Input::keys.erase(Input::keys.begin() + i);
          i--;
        }
      }

      Input::upKeys.push_back(event.key.keysym.sym);
    }
    else if(event.type == SDL_MOUSEBUTTONUP)
    {
      for(int i = 0; i < Input::mouseButtons.size(); i++)
      {
        if(Input::mouseButtons.at(i) == event.button.button)
        {
          Input::mouseButtons.erase(Input::mouseButtons.begin() + i);
          i--;
        }
      }

      Input::upMouseButtons.push_back(event.button.button);
    }
    else if(event.type == SDL_MOUSEBUTTONDOWN)
    {
      for(int i = 0; i < Input::mouseButtons.size(); i++)
      {
        if(Input::mouseButtons.at(i) == event.button.button)
        {
          continue;
        }
      }

      Input::mouseButtons.push_back(event.button.button);
      Input::downMouseButtons.push_back(event.button.button);
    }
  }

  for(int i = 0; i < gameObjects.size(); i++)
  {
    gameObjects.at(i)->update();
  }

  for(int i = 0; i < gameObjects.size(); i++)
  {
    if(gameObjects.at(i)->destroyed == true)
    {
      gameObjects.at(i)->destroy();
      gameObjects.erase(gameObjects.begin() + i);
      i--;
    }
  }

  glClearColor(32.0f / 255.0f, 32.0f / 255.0f, 32.0f / 255.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glViewport(0, 0, Screen::getWidth(), Screen::getHeight());

  for(int h = 0; h < Camera::getAllCameras()->size(); h++)
  {
    if(Camera::getAllCameras()->at(h)->getGameObject()->getActive() == false)
    {
      continue;
    }

    Camera::current = Camera::getAllCameras()->at(h);

    if(Camera::current->targetTexture != NULL)
    {
      Camera::current->targetTexture->setEnabled(true);
    }

    //glClearColor(0.2f, 0.2f, 0.5f, 1.0f);
    glClearColor(49.0f / 255.0f, 77.0f / 255.0f, 121.0f / 255.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for(int i = 0; i < gameObjects.size(); i++)
    {
      gameObjects.at(i)->render();
    }

    if(Camera::current->targetTexture != NULL)
    {
      Camera::current->targetTexture->setEnabled(false);
    }
  }

  for(int i = 0; i < gameObjects.size(); i++)
  {
    gameObjects.at(i)->gui();
  }

  SDL_GL_SwapBuffers();

  if(levelChange != "")
  {
    loadedLevelName = levelChange;
    levelChange = "";
    loadLevel();
  }
}

void Application::quit()
{
  running = false;
}

void Application::loadLevel()
{
  for(int i = 0; i < gameObjects.size(); i++)
  {
    if(gameObjects.at(i)->destroyOnLoad == true)
    {
      gameObjects.at(i)->destroy();
      gameObjects.erase(gameObjects.begin() + i);
      i--;
    }
  }

  for(int i = 0; i < Resources::objects.size(); i++)
  {
    if(Resources::objects.at(i)->destroyOnLoad == true)
    {
      Resources::objects.erase(Resources::objects.begin() + i);
      Resources::paths.erase(Resources::paths.begin() + i);
      i--;
    }
  }

  for(int i = 0; i < gameObjects.size(); i++)
  {
    gameObjects.at(i)->levelWasLoaded();
  }
}

void Application::loadLevel(std::string path)
{
  if(running == true)
  {
    levelChange = path;
  }
  else
  {
    loadedLevelName = path;
    loadLevel();
  }
}

std::string Application::getLoadedLevelName()
{
  return loadedLevelName;
}

std::string Application::getDataPath()
{
  return dataPath;
}

}

}

