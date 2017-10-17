/************************************************
*                  Console.hpp                  *
*************************************************
*          This file is a part of:              *
*               COLUMBUS COMPILER               *
*************************************************
*             Nikolay(Columbus) Red             *
*                   17.10.2017                  *
*************************************************/

#pragma once

#include <iostream>
#include <string>
#include <cstdlib>

#include <System.hpp>

namespace ColumbusCompiler
{

  void C_Info(std::string aMessage);

  void C_Warning(std::string aMessage);

  void C_Error(std::string aMessage);

  void C_FatalError(std::string aMessage);

  void C_Success(std::string aMessage);

  void C_Initialization(std::string aMessage);

}
