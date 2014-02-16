#include "SceneManager.h"

#include <mutiny/mutiny.h>

#include <ctime>
#include <iostream>

using namespace mutiny::engine;

void safe_main(int argc, char* argv[])
{
  srand(time(NULL));
  Application::init(argc, argv);

  Application::loadLevel("menu");

  GameObject* smGo = new GameObject();
  smGo->addComponent<SceneManager>();

  Application::run();
}

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
