#include "SceneManager.h"

#include <mutiny/mutiny.h>

#include <iostream>

using namespace mutiny::engine;

void safe_main(int argc, char* argv[])
{
  Application application(argc, argv);

  application.loadLevel("Main");

  GameObject* smGo = new GameObject();
  smGo->addComponent<SceneManager>();

  application.run();
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
