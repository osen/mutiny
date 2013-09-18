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
#include "Texture2d.h"
#include "Gui.h"

#include <GL/glew.h>
#include <SDL/SDL.h>

#ifdef EMSCRIPTEN
#include <emscripten.h>
#endif

#include <unistd.h>

#include <functional>
#include <iostream>

namespace mutiny
{

namespace engine
{

Application* Application::instance = NULL;

Application::Application(int argc, char* argv[])
{
  if(instance != NULL)
  {
    std::cout << "Error: Already initialized" << std::endl;
    throw std::exception();
  }

  instance = this;
  initialized = true;
  running = false;

  this->argc = argc;

  for(int i = 0; i < argc; i++)
  {
    this->argv.push_back(argv[i]);
  }

  setupPaths();

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

  Material::defaultMaterial = Resources::load<Material>("shaders/default_diffuse");
  //if(Material::defaultMaterial == NULL) { throw Exception("Failed to load 'shaders/default_diffuse'"); }
  if(Material::defaultMaterial == NULL) { throw std::exception(); }
  Object::dontDestroyOnLoad(Material::defaultMaterial);

  Material::guiMaterial = Resources::load<Material>("shaders/default_gui");
  Object::dontDestroyOnLoad(Material::guiMaterial);

  Material::particleMaterial = Resources::load<Material>("shaders/default_particle");
  Object::dontDestroyOnLoad(Material::particleMaterial);

  GuiSkin::defaultGuiSkin.reset(new GuiSkin());

  initialized = true;

  //displaySplash();
}

void Application::setupPaths()
{
#ifdef EMSCRIPTEN
  engineDataPath = "share/mutiny";
  dataPath = std::string("share/") + GAMENAME;
#elif WINDOWS
  error
#else
  engineDataPath = "share/mutiny";
  dataPath = std::string("share/") + GAMENAME;
#endif
}

void Application::displaySplash()
{
  glClearColor(1, 1, 1, 1.0f);
  Texture2d* tex2 = Resources::load<Texture2d>("images/loading");
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  Gui::drawTexture(Rect(0, 0, 500, 500), tex2);
  SDL_GL_SwapBuffers();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  Gui::drawTexture(Rect(0, 0, 500, 500), tex2);
  SDL_GL_SwapBuffers();
}

void Application::run()
{
  if(running == true)
  {
    std::cout << "Error: Already running" << std::endl;
    throw std::exception();
  }

  //displaySplash();

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

  Screen::width = instance->screen->w;
  Screen::height = instance->screen->h;

  Input::downKeys.clear();
  Input::upKeys.clear();
  Input::downMouseButtons.clear();
  Input::upMouseButtons.clear();

  while(SDL_PollEvent(&event))
  {
    if(event.type == SDL_QUIT)
    {
      instance->running = false;
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

  for(int i = 0; i < instance->gameObjects.size(); i++)
  {
    instance->gameObjects.at(i)->update();
  }

  std::vector<std::shared_ptr<GameObject> > destroyedGos;
  for(int i = 0; i < instance->gameObjects.size(); i++)
  {
    if(instance->gameObjects.at(i)->destroyed == true)
    {
      instance->gameObjects.at(i)->destroy();
      destroyedGos.push_back(instance->gameObjects.at(i));
      instance->gameObjects.erase(instance->gameObjects.begin() + i);
      i--;
    }
  }
  destroyedGos.clear();

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

    for(int i = 0; i < instance->gameObjects.size(); i++)
    {
      instance->gameObjects.at(i)->render();
    }

    if(Camera::current->targetTexture != NULL)
    {
      Camera::current->targetTexture->setEnabled(false);
    }
  }

  for(int i = 0; i < instance->gameObjects.size(); i++)
  {
    instance->gameObjects.at(i)->gui();
  }

  SDL_GL_SwapBuffers();

  if(instance->levelChange != "")
  {
    instance->loadedLevelName = instance->levelChange;
    instance->levelChange = "";
    loadLevel();
  }
}

void Application::quit()
{
  instance->running = false;
}

void Application::loadLevel()
{
  std::vector<std::shared_ptr<GameObject> > destroyedGos;
  for(int i = 0; i < instance->gameObjects.size(); i++)
  {
    if(instance->gameObjects.at(i)->destroyOnLoad == true)
    {
      instance->gameObjects.at(i)->destroy();
      destroyedGos.push_back(instance->gameObjects.at(i));
      instance->gameObjects.erase(instance->gameObjects.begin() + i);
      i--;
    }
  }
  destroyedGos.clear();

  for(int i = 0; i < Resources::objects.size(); i++)
  {
    if(Resources::objects.at(i)->destroyOnLoad == true)
    {
      Resources::objects.erase(Resources::objects.begin() + i);
      Resources::paths.erase(Resources::paths.begin() + i);
      i--;
    }
  }

  for(int i = 0; i < instance->gameObjects.size(); i++)
  {
    instance->gameObjects.at(i)->levelWasLoaded();
  }
}

void Application::loadLevel(std::string path)
{
  if(instance->running == true)
  {
    instance->levelChange = path;
  }
  else
  {
    instance->loadedLevelName = path;
    loadLevel();
  }
}

std::string Application::getLoadedLevelName()
{
  return instance->loadedLevelName;
}

std::string Application::getDataPath()
{
  return instance->dataPath;
}

int Application::getArgc()
{
  return instance->argc;
}

std::string Application::getArgv(int i)
{
  return instance->argv.at(i);
}

}

}

