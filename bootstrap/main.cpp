#include "EngineBuilder.h"
#include "ProjectBuilder.h"
#include "Environment.h"
#include "arc.h"

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

  arc<Environment> environment = Environment::create(args);

  if(environment->isMutinyAvailable() == true)
  {
    arc<EngineBuilder> engineBuilder = EngineBuilder::create(environment);
    engineBuilder->removeOrphanedObjects();
    engineBuilder->buildOutOfDateObjects();
  }

  arc<ProjectBuilder> projectBuilder = ProjectBuilder::create(environment);
  projectBuilder->removeOrphanedObjects();
  projectBuilder->buildOutOfDateObjects();
  projectBuilder->generateOutOfDateOutput();

  return 0;
}
