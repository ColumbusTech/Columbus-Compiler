#pragma once

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <Types.hpp>
#include <Console.hpp>

namespace ColumbusCompiler
{

  class C_Interpreter
  {
  private:
    bool mInited = false;

    std::string mSrcFile;
    std::string mDstFile;

    std::vector<C_Type> mTypes;

    bool load();
    bool getErrors();
    void save();
  public:
    C_Interpreter(int argc, char** argv);

    void compile();

    ~C_Interpreter();
  };

}
