#include "Application.h"
#include "GameObject.h"
#include "Component.h"
#include "Camera.h"
#include "Material.h"
#include "Screen.h"
#include "_Time.h"
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

#ifdef WINDOWS
#include <windows.h>
#else
#include <unistd.h>
#endif

#include <functional>
#include <iostream>

namespace mutiny
{

namespace engine
{

std::shared_ptr<SDL_Surface> Application::screen;
bool Application::running = false;
bool Application::initialized = false;
std::string Application::loadedLevelName;
std::vector<std::shared_ptr<GameObject> > Application::gameObjects;
std::string Application::levelChange;
std::string Application::dataPath;
std::string Application::engineDataPath;

int Application::argc = 0;
std::vector<std::string> Application::argv;

void Application::init(int argc, char* argv[])
{
  if(initialized == true)
  {
    return;
  }

  initialized = true;
  running = false;

  Application::argc = argc;

  for(int i = 0; i < argc; i++)
  {
    Application::argv.push_back(argv[i]);
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
  std::string dirname;
  std::string basename;

#ifdef EMSCRIPTEN
  engineDataPath = "share/mutiny";
  dataPath = "share/_data";
#elif WINDOWS
  char strExePath [MAX_PATH];

  GetModuleFileName (NULL, strExePath, MAX_PATH);
  dirname = strExePath;
  dirname = dirname.substr(0, dirname.find_last_of("\\"));
  dirname = dirname.substr(0, dirname.find_last_of("\\"));

  engineDataPath = "share/mutiny";
  dataPath = "share/mygame";
#else
  FILE* process = NULL;
  std::string command;
  char buffer[8];

  command = "cd `dirname \\`which " + std::string(argv.at(0)) + "\\``; cd ..; pwd | tr -d '\n'";
  process = popen(command.c_str(), "r");

  if(process == NULL)
  {
    throw std::exception();
    //throw Exception("Failed to open child process");
  }

  while(fgets(buffer, 7, process) != NULL)
  {
    dirname += buffer;
  }

  pclose(process);

  command = "basename " + std::string(argv.at(0)) + " | tr -d '\n'";
  process = popen(command.c_str(), "r");

  if(process == NULL)
  {
    throw std::exception();
    //throw Exception("Failed to open child process");
  }

  while(fgets(buffer, 7, process) != NULL)
  {
    basename += buffer;
  }

  pclose(process);

  engineDataPath = dirname + "/share/mutiny";
  dataPath = dirname + "/share/" + basename;
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

  std::vector<std::shared_ptr<GameObject> > destroyedGos;
  for(int i = 0; i < gameObjects.size(); i++)
  {
    if(gameObjects.at(i)->destroyed == true)
    {
      gameObjects.at(i)->destroy();
      destroyedGos.push_back(gameObjects.at(i));
      gameObjects.erase(gameObjects.begin() + i);
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
  std::vector<std::shared_ptr<GameObject> > destroyedGos;
  for(int i = 0; i < gameObjects.size(); i++)
  {
    if(gameObjects.at(i)->destroyOnLoad == true)
    {
      gameObjects.at(i)->destroy();
      destroyedGos.push_back(gameObjects.at(i));
      gameObjects.erase(gameObjects.begin() + i);
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

int Application::getArgc()
{
  return argc;
}

std::string Application::getArgv(int i)
{
  return argv.at(i);
}

}

}

