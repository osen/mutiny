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

#include "Transform.h"

#include "internal/Internal.h"
#include "internal/Util.h"

#include <GL/glew.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

#ifdef EMSCRIPTEN
#include <emscripten.h>
#endif

#ifdef WINDOWS
#include <windows.h>
#else
#include <unistd.h>
#endif

#include <ctime>
#include <functional>
#include <iostream>
#include <fstream>

namespace mutiny
{

namespace engine
{

std::shared_ptr<internal::Internal> Application::_internal;
std::vector<std::shared_ptr<GameObject> > Application::gameObjects;
SDL_Surface* Application::screen;
bool Application::running;
bool Application::initialized;
std::string Application::loadedLevelName;
std::string Application::levelChange;
std::string Application::dataPath;
std::string Application::engineDataPath;
int Application::argc;
std::vector<std::string> Application::argv;

void Application::init(int argc, char* argv[])
{
  if(_internal.get() != NULL)
  {
    return;
  }

  _internal.reset(new internal::Internal());
  running = false;
  Application::argc = argc;

  for(int i = 0; i < argc; i++)
  {
    Application::argv.push_back(argv[i]);
  }

  srand(time(NULL));
  setupPaths();
  //std::cout << "Paths: " << engineDataPath << " " << dataPath << std::endl;

  if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
  {
    std::cout << "Error: Failed to initialize" << std::endl;
    throw std::exception();
  }

  //screen.reset(SDL_SetVideoMode(800, 600, 32, SDL_OPENGL | SDL_RESIZABLE), std::bind(SDL_Quit));
  screen = SDL_SetVideoMode(800, 600, 32, SDL_OPENGL | SDL_RESIZABLE);

  //if(screen.get() == NULL)
  if(screen == NULL)
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

  if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
  {
    std::cout << "Audio failed to initialize" << std::endl;
    throw std::exception();
  }

  Material::defaultMaterial = Resources::load<Material>("shaders/default_diffuse");
  //if(Material::defaultMaterial == NULL) { throw Exception("Failed to load 'shaders/default_diffuse'"); }
  if(Material::defaultMaterial == NULL) { throw std::exception(); }
  Object::dontDestroyOnLoad(Material::defaultMaterial);

  Material::guiMaterial = Resources::load<Material>("shaders/default_gui");
  Object::dontDestroyOnLoad(Material::guiMaterial);

  Material::particleMaterial = Resources::load<Material>("shaders/default_particle");
  Object::dontDestroyOnLoad(Material::particleMaterial);

  _internal->graphicsDefaultMaterial = Resources::load<Material>("shaders/Internal-GUITexture");
  Object::dontDestroyOnLoad(_internal->graphicsDefaultMaterial);

  _internal->defaultGuiSkin.reset(new GuiSkin());

  RenderTexture::active = NULL;
  Camera::current = NULL;
  Camera::main = NULL;

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
  basename = dirname.substr(dirname.find_last_of("\\"));
  basename = basename.substr(0, basename.length() - 4);
  dirname = dirname.substr(0, dirname.find_last_of("\\"));
  dirname = dirname.substr(0, dirname.find_last_of("\\"));

  engineDataPath = dirname + "/share/mutiny";
  dataPath = dirname + "/share" + basename;
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

void Application::destroy()
{
  if(_internal.get() == NULL)
  {
    throw std::exception();
  }

  // TODO: Running is a flag, not a reliable state
  if(running == true)
  {
    throw std::exception();
  }

  _internal.reset();

  Camera::allCameras.clear();
  gameObjects.clear();
  Resources::paths.clear();
  Resources::objects.clear();

  SDL_Quit();
}

void Application::displaySplash()
{
  // set timeout
  // add gui game object
  // when timeout done, change to next scene
}

void Application::run()
{
  if(running == true)
  {
    return;
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
    else if(event.type == SDL_VIDEORESIZE)
    {
      Screen::width = event.resize.w;
      Screen::height = event.resize.h;
      screen = SDL_SetVideoMode(Screen::width, Screen::height, 32, SDL_OPENGL | SDL_RESIZABLE);
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

    if(Camera::getCurrent()->targetTexture != NULL)
    {
      RenderTexture::setActive(Camera::getCurrent()->targetTexture);
    }

    //glClearColor(0.2f, 0.2f, 0.5f, 1.0f);
    Color clearColor = Camera::getCurrent()->getBackgroundColor();
    glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for(int i = 0; i < gameObjects.size(); i++)
    {
      if((Camera::getCurrent()->getCullMask() & gameObjects.at(i)->getLayer()) !=
        gameObjects.at(i)->getLayer())
      {
        continue;
      }

      gameObjects.at(i)->render();
    }

    if(Camera::getCurrent()->targetTexture != NULL)
    {
      RenderTexture::setActive(NULL);
    }
  }

  for(int i = 0; i < gameObjects.size(); i++)
  {
    gameObjects.at(i)->postRender();
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

void Application::loadLevelAdditive(std::string path)
{
  std::ifstream file;
  std::string line;
  std::vector<std::string> tokens;
  GameObject* go;

  file.open(std::string(dataPath + "/" + path + ".scene").c_str());

  if(file.is_open() == false)
  {
    Debug::logWarning("Failed to open scene file '" + path + ".scene'");
    return;
  }

  while(file.eof() == false)
  {
    getline(file, line);
    tokens.clear();
    internal::Util::splitStringWhitespace(line, &tokens);

    if(tokens.size() < 1)
    {
      continue;
    }

    if(tokens.at(0) == "go")
    {
      if(tokens.size() > 1)
      {
        go = GameObject::createModel(tokens.at(1));
      }
      else
      {
        go = new GameObject();
      }
    }
    else if(tokens.at(0) == "n")
    {
      go->setName(tokens.at(1));
    }
    else if(tokens.at(0) == "tp")
    {
      go->getTransform()->setPosition(Vector3(
        atof(tokens.at(1).c_str()),
        atof(tokens.at(2).c_str()),
        atof(tokens.at(3).c_str())));
    }
    else if(tokens.at(0) == "tr")
    {
      go->getTransform()->setRotation(Vector3(
        atof(tokens.at(1).c_str()),
        atof(tokens.at(2).c_str()),
        atof(tokens.at(3).c_str())));
    }
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

internal::Internal* Application::getInternal()
{
  return _internal.get();
}

}

}

