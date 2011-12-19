//
/// \file bot/output.cpp
/// \brief Output functions
//

#include "output.h"

#include <iostream>

namespace JulieSu
{
	namespace Output
	{
		void write (std::string msg)
		{
			std::cout << msg << std::endl;
		}
	}
}

