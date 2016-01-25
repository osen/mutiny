#include <iostream>
#include <fstream>
#include <cstdlib>

class Component
{
public:
  Component()
  {
    std::cout << "Component" << std::endl;
  }

  virtual ~Component()
  {
    std::cout << "~Component" << std::endl;
  }
};

class TestComponent : public Component
{
public:
  TestComponent()
  {
    std::cout << "TestComponent" << std::endl;
  }

  virtual ~TestComponent()
  {
    std::cout << "~TestComponent" << std::endl;
  }
};


int main(int argc, char* argv[])
{
  std::cout << "Hello World" << std::endl;

  Component* tc = new(calloc(1, sizeof(*tc))) TestComponent();
  tc->~Component();
  free(tc);

  std::ifstream file("data/file.txt");

  if(file.is_open() == false)
  {
    std::cout << "Error: Failed to open file" << std::endl;
    return 1;
  }

  while(file.eof() == false)
  {
    std::string line;
    getline(file, line);

    std::cout << line << std::endl;
  }

  return 0;
}

