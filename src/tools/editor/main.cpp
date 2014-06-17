#include "SceneManager.h"

#include <mutiny/mutiny.h>

#include <iostream>
#include <exception>

using namespace mutiny::engine;

void safe_main(int argc, char* argv[])
{
  Application::init(argc, argv);
  Application::setTitle("Mutiny - Project Wizard");

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
