#pragma once

#include <string>

namespace ColumbusCompiler
{

  //Types
  //0 == begin
  //1 == end
  //2 == mark
  //3 == clearall
  //4 == setall
  //5 == clear
  //6 == set
  //7 == goto

  struct C_Type
  {
    int type = -1;
    int str = 0;

    std::string line;

    bool afterType = false;

    int afterTypeI = -10000;
    int afterTypeH = 0x00;
    std::string afterTypeS;

    bool endOperator = false;
  };

}
