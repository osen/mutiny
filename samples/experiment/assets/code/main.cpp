#include "SceneManager.h"

#include <mutiny/mutiny.h>

#include <iostream>

using namespace mutiny::engine;

void safe_main(int argc, char* argv[])
{
  Application::init(argc, argv);

  Application::loadLevel("introduction");

  GameObject* smGo = new GameObject();
  smGo->addComponent<SceneManager>();

  Application::run();
}

#if defined(_WIN32) && !defined(_MSC_VER)
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
  int argc = 1;
  char* argv[1];
  argv[0] = "experiment.exe";
  safe_main(argc, argv);

  return 0;
}
#else
int main(int argc, char* argv[])
{
  //try
  //{
    safe_main(argc, argv);

    return 0;
  //}
  //catch(std::exception& e)
  //{
  //  std::cout << "Exception: " << e.what() << std::endl;

  //  return 1;
  //}
}
#endif
