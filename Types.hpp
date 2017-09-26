#pragma once

#include <string>

namespace ColumbusCompiler
{

  //Types
  //0 == begin
  //1 == end
  //2 == mark
  //3 == clearall
  //4 == set
  //5 == goto

  struct C_Type
  {
    int type = -1;
    int str = 0;

    std::string line;

    bool endOperator;
  };

}
