#include <iostream>
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

  ~TestComponent()
  {
    std::cout << "~TestComponent" << std::endl;
  }
};


int main(int argc, char* argv[])
{
  std::cout << "Hello World" << std::endl;

  TestComponent* tc = new(calloc(1, sizeof(*tc))) TestComponent();
  tc->~Component();
  free(tc);

  return 0;
}
