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
#include "Graphics.h"
#include "Transform.h"

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

std::vector<std::shared_ptr<GameObject> > Application::gameObjects;
SDL_Surface* Application::screen;
bool Application::running;
std::string Application::loadedLevelName;
std::string Application::levelChange;
std::string Application::dataPath;
std::string Application::engineDataPath;
int Application::argc;
std::vector<std::string> Application::argv;

void Application::init(int argc, char* argv[])
{
  running = false;
  Application::argc = argc;

  for(int i = 0; i < argc; i++)
  {
    Application::argv.push_back(argv[i]);
  }

  srand(time(NULL));
  setupPaths();

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

  setTitle("Mutiny Engine");

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

  Material::defaultMaterial = Resources::load<Material>("shaders/Internal-DefaultDiffuseTexture");
  //if(Material::defaultMaterial == NULL) { throw Exception("Failed to load 'shaders/Internal-DefaultDiffuseTexture'"); }
  if(Material::defaultMaterial == NULL) { throw std::exception(); }
  Object::dontDestroyOnLoad(Material::defaultMaterial);

  Material::guiMaterial = Resources::load<Material>("shaders/default_gui");
  Object::dontDestroyOnLoad(Material::guiMaterial);

  Material::particleMaterial = Resources::load<Material>("shaders/default_particle");
  Object::dontDestroyOnLoad(Material::particleMaterial);

  Graphics::defaultMaterial = Resources::load<Material>("shaders/Internal-GUITexture");
  Object::dontDestroyOnLoad(Graphics::defaultMaterial);

  GuiSkin::_default = new GuiSkin();
  Material::current = NULL;
  RenderTexture::active = NULL;
  Camera::current = NULL;
  Camera::_main = NULL;
  Gui::skin = NULL;
  Graphics::renderTarget = NULL;

  //displaySplash();
}

void Application::setTitle(std::string title)
{
  SDL_WM_SetCaption(title.c_str(), NULL);
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

  //std::cout << "Paths: " << engineDataPath << " " << dataPath << std::endl;
}

void Application::destroy()
{
  // TODO: Running is a flag, not a reliable state
  if(running == true)
  {
    throw std::exception();
  }

  delete GuiSkin::_default;

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
  //emscripten_set_main_loop(loop, 60, true);
  emscripten_set_main_loop(loop, 0, true);
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

#ifdef EMSCRIPTEN
  // Does not allow SDL_Delay. Assumes it is in an infinite loop.
#else
  float idealTime = 1.0f / 60.0f;

  if(idealTime > Time::deltaTime)
  {
    // Sleep off remaining time
    SDL_Delay((idealTime - Time::deltaTime) * 1000.0f);
    //usleep((idealTime - Time::deltaTime) * 1000000.0f);
    //Time::deltaTime = idealTime;
  }
#endif

  static float lastTime = SDL_GetTicks();
  float time = SDL_GetTicks();
  float diff = time - lastTime;
  Time::deltaTime = diff / 1000.0f;
  lastTime = time;

  Screen::width = screen->w;
  Screen::height = screen->h;

  while(SDL_PollEvent(&event))
  {
    if(event.type == SDL_QUIT)
    {
      running = false;
    }
    else if(event.type == SDL_VIDEORESIZE)
    {
      reshape(event.resize.w, event.resize.h);
    }
#ifdef EMSCRIPTEN
    else if(event.type == SDL_FINGERMOTION)
    {
      motion(event.tfinger.x * Screen::getWidth(),
             event.tfinger.y * Screen::getHeight());
    }
#endif
    else if(event.type == SDL_MOUSEMOTION)
    {
      motion(event.motion.x, event.motion.y);
    }
#ifdef EMSCRIPTEN
    else if(event.type == SDL_FINGERDOWN)
    {
      motion(event.tfinger.x * Screen::getWidth(),
             event.tfinger.y * Screen::getHeight());

      mouse(0, SDL_MOUSEBUTTONDOWN, Input::mousePosition.x, Input::mousePosition.y);
    }
#endif
    else if(event.type == SDL_MOUSEBUTTONDOWN)
    {
      mouse(event.button.button, SDL_MOUSEBUTTONDOWN, Input::mousePosition.x,
        Input::mousePosition.y);
    }
#ifdef EMSCRIPTEN
    else if(event.type == SDL_FINGERUP)
    {
      motion(event.tfinger.x * Screen::getWidth(),
             event.tfinger.y * Screen::getHeight());

      mouse(0, SDL_MOUSEBUTTONUP, Input::mousePosition.x, Input::mousePosition.y);
    }
#endif
    else if(event.type == SDL_MOUSEBUTTONUP)
    {
	  mouse(event.button.button, SDL_MOUSEBUTTONUP, Input::mousePosition.x,
        Input::mousePosition.y);
    }
    else if(event.type == SDL_KEYDOWN)
    {
      keyboard(event.key.keysym.sym, Input::mousePosition.x, Input::mousePosition.y);
    }
    else if(event.type == SDL_KEYUP)
    {
      keyboardUp(event.key.keysym.sym, Input::mousePosition.x, Input::mousePosition.y);
    }
  }

  idle();
  display();

  Input::downKeys.clear();
  Input::upKeys.clear();
  Input::downMouseButtons.clear();
  Input::upMouseButtons.clear();

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

void Application::reshape(int width, int height)
{
  Screen::width = width;
  Screen::height = height;
  screen = SDL_SetVideoMode(Screen::width, Screen::height, 32, SDL_OPENGL | SDL_RESIZABLE);
}

void Application::display()
{
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
}

void Application::idle()
{
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
}

void Application::motion(int x, int y)
{
  Input::mousePosition.x = x;
  Input::mousePosition.y = y;
}

void Application::mouse(int button, int state, int x, int y)
{
  if(state == SDL_MOUSEBUTTONDOWN)
  {
    for(int i = 0; i < Input::mouseButtons.size(); i++)
    {
      if(Input::mouseButtons.at(i) == button)
      {
        return;
      }
    }

    Input::mouseDownPosition.x = x;
    Input::mouseDownPosition.y = y;
    Input::mouseButtons.push_back(button);
    Input::downMouseButtons.push_back(button);
  }
  else
  {
    for(int i = 0; i < Input::mouseButtons.size(); i++)
    {
      if(Input::mouseButtons.at(i) == button)
      {
        Input::mouseButtons.erase(Input::mouseButtons.begin() + i);
        i--;
      }
    }

    Input::upMouseButtons.push_back(button);
    //std::cout << (int)button << std::endl;
  }
}

void Application::keyboard(int key, int x, int y)
{
  //std::cout << key << std::endl;
  for(int i = 0; i < Input::keys.size(); i++)
  {
    if(Input::keys.at(i) == key)
    {
      return;
    }
  }

  Input::keys.push_back(key);
  Input::downKeys.push_back(key);
}

void Application::keyboardUp(int key, int x, int y)
{
  for(int i = 0; i < Input::keys.size(); i++)
  {
    if(Input::keys.at(i) == key)
    {
      Input::keys.erase(Input::keys.begin() + i);
      i--;
    }
  }

  Input::upKeys.push_back(key);
}

}

}

