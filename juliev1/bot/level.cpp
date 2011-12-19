//
/// \file bot/level.cpp
/// \brief User admin levels
//

#include "level.h"

namespace JulieSu
{
	Level levelFromString (std::string string)
	{
		if (string == "ignore")
			return LEVEL_IGNORE;
		else if (string == "normal")
			return LEVEL_NORMAL;
		else if (string == "admin")
			return LEVEL_ADMIN;
		else
			return LEVEL_NORMAL; // Default
	}

	std::string stringFromLevel (Level level)
	{
		switch (level)
		{
			case LEVEL_IGNORE:
				return "ignore";

			case LEVEL_NORMAL:
				return "normal";

			case LEVEL_ADMIN:
				return "admin";

			default:
				return "unknown";
		}
	}

}
