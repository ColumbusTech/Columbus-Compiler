#pragma once

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
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
    std::vector<std::string> mMarks;

    std::map<int, std::string> mSyntax = { {0, "begin"}, {1, "end"}, {2, "mark"}, {3, "goto"},
    {4, "clearall"}, {5, "setall"}, {6, "clear"}, {7, "set"} };

    bool load();
    bool getErrors();
    void save();

    bool isStringNumber(std::string str);

    int getType(std::string str);
    bool getEndOperator(int type, std::string str);
  public:
    C_Interpreter(int argc, char** argv);

    void compile();

    ~C_Interpreter();
  };

}
