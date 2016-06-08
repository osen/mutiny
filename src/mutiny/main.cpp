#include "Application.h"
#include "Exception.h"
#include "internal/platform.h"

#ifdef USE_WINAPI
  #include "windows.h"
#endif

#include <iostream>

void mutiny_main();

namespace mutiny
{

namespace engine
{

void safe_main(int argc, char* argv[])
{
  Application::init(argc, argv);

  mutiny_main();

  Application::run();

  Application::destroy();
}

}

}

int main(int argc, char* argv[])
{
/*
  try
  {
*/
    mutiny::engine::safe_main(argc, argv);

    return 0;
/*
  }
  catch(mutiny::engine::Exception& e)
  {
    std::cout << "Mutiny Exception: " << e.what() << std::endl;

#ifdef USE_WINAPI

    MessageBox(0, e.what(), "Mutiny Engine - Exception", 0);

#endif

    return 1;
  }
  catch(std::exception& e)
  {
    std::cout << "Exception: " << e.what() << std::endl;

#ifdef USE_WINAPI

    MessageBox(0, e.what(), "Exception", 0);

#endif

    return 1;
  }
*/
}
