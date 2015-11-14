#include "EngineBuilder.h"
#include "ProjectBuilder.h"
#include "Environment.h"

#include <iostream>
#include <vector>
#include <string>

int main(int argc, char* argv[])
{
  std::cout << "Mutiny Build System" << std::endl;

  std::vector<std::string> args;

  for(int i = 0; i < argc; i++)
  {
    args.push_back(argv[i]);
  }

  std::shared_ptr<Environment> environment = Environment::create(args);

  std::shared_ptr<EngineBuilder> engineBuilder = EngineBuilder::create(environment);
  engineBuilder->removeOrphanedObjects();
  engineBuilder->buildOutOfDateObjects();

  std::shared_ptr<ProjectBuilder> projectBuilder = ProjectBuilder::create(environment);
  projectBuilder->removeOrphanedObjects();
  projectBuilder->buildOutOfDateObjects();
  projectBuilder->generateOutOfDateOutput();

  return 0;
}
