#pragma once

#include <string>

namespace ColumbusCompiler
{

  //Types
  //0 == begin
  //1 == end
  //2 == mark
  //3 == goto
  //4 == clearall
  //5 == setall
  //6 == clear
  //7 == set

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
