/************************************************
*                  System.cpp                   *
*************************************************
*          This file is a part of:              *
*               COLUMBUS COMPILER               *
*************************************************
*             Nikolay(Columbus) Red             *
*                   17.10.2017                  *
*************************************************/

#include <System.hpp>

namespace ColumbusCompiler
{

	//////////////////////////////////////////////////////////////////////////////
	//Return current Operating System
	std::string C_GetSystem()
	{
		#ifdef _WIN32
				return "Win32";
		#endif

		#ifdef _WIN64
				return "Win64";
		#endif

		#ifdef __LINUX__
				return "Linux";
		#endif

		#ifdef __unix
				return "Unix";
		#endif

		#ifdef __posix
				return "POSIX";
		#endif

		#ifdef __APPLE__
				return "Apple";
		#endif
	}

}
