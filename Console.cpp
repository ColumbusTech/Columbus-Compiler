/************************************************
*                  Console.hpp                  *
*************************************************
*          This file is a part of:              *
*               COLUMBUS COMPILER               *
*************************************************
*             Nikolay(Columbus) Red             *
*                   17.10.2017                  *
*************************************************/

#include <Console.hpp>

namespace ColumbusCompiler
{

  //////////////////////////////////////////////////////////////////////////////
  void C_Info(std::string aMessage)
  {
    std::string colinf = "\x1b[37;1m[INFO]:\x1b[0m ";
    std::string colmes = "\x1b[37;1m" + aMessage + "\x1b[0m";

    if (C_GetSystem() == "Win32" || C_GetSystem() == "Win64")
      std::cout << "[INFO]: " << aMessage << std::endl;
    else
      std::cout << colinf << colmes << std::endl;
  }
  //////////////////////////////////////////////////////////////////////////////
  void C_Warning(std::string aMessage)
  {
    std::string colwar = "\x1b[33;1m[WARNING]:\x1b[0m ";
    std::string colmes = "\x1b[37;1m" + aMessage + "\x1b[0m";

    if (C_GetSystem() == "Win32" || C_GetSystem() == "Win64")
      std::cout << "[WARNING] " << aMessage << std::endl;
    else
      std::cout << colwar << colmes << std::endl;
  }
  //////////////////////////////////////////////////////////////////////////////
  void C_Error(std::string aMessage)
  {
    std::string colerr = "\x1b[31;1m[ERROR]:\x1b[0m ";
    std::string colmes = "\x1b[37;1m" + aMessage + "\x1b[0m";

    if (C_GetSystem() == "Win32" || C_GetSystem() == "Win64")
      std::cout << "[ERROR] " << aMessage << std::endl;
    else
      std::cout << colerr << colmes << std::endl;
  }
  //////////////////////////////////////////////////////////////////////////////
  void C_FatalError(std::string aMessage)
  {
    std::string colfer = "\x1b[35;1m[FATAL ERROR]:\x1b[0m ";
    std::string colmes = "\x1b[37;1m" + aMessage + "\x1b[0m";

    if (C_GetSystem() == "Win32" || C_GetSystem() == "Win64")
      std::cout << "[FATAL ERROR] " << aMessage << std::endl;
    else
      std::cout << colfer << colmes << std::endl;

    exit(1);
  }
  //////////////////////////////////////////////////////////////////////////////
  void C_Success(std::string aMessage)
  {
    std::string colsuc = "\x1b[32;1m[SUCCESS]:\x1b[0m ";
    std::string colmes = "\x1b[37;1m" + aMessage + "\x1b[0m";

    if (C_GetSystem() == "Win32" || C_GetSystem() == "Win64")
      std::cout << "[SUCCESS] " << aMessage << std::endl;
    else
      std::cout << colsuc << colmes << std::endl;
  }
  //////////////////////////////////////////////////////////////////////////////
  void C_Initialization(std::string aMessage)
  {
    std::string colini = "\x1b[36;1m[INITIALIZATION]:\x1b[0m ";
    std::string colmes = "\x1b[37;1m" + aMessage + "\x1b[0m";

    if (C_GetSystem() == "Win32" || C_GetSystem() == "Win64")
      std::cout << "[INITIALIZATION] " << aMessage << std::endl;
    else
      std::cout << colini << colmes << std::endl;
  }

}
