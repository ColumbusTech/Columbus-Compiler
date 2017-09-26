#include <Compiler.hpp>

using namespace ColumbusCompiler;

int main(int argc, char** argv)
{
  C_Interpreter compiler(argc, argv);

  compiler.compile();

  return 0;
}
