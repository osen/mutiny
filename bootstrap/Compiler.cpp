#include "Compiler.h"
#include "Util.h"

std::shared_ptr<Compiler> Compiler::create()
{
  static Compiler s;
  std::shared_ptr<Compiler> rtn(new Compiler(s));

  return rtn;
}

void Compiler::compile(std::string sourceUnit, std::string output)
{
  std::string result = Util::execute("g++ -std=c++11 -c " +
    sourceUnit +
    " -o " +
    output);
}
