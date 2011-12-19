//
/// \file bot/level.h
/// \brief User admin levels
//

#ifndef BOT_LEVEL_H
#define BOT_LEVEL_H

#include <string>

namespace JulieSu
{
	// To add more, just add it between the ranks you want
	// Higher ranks give more priviliges
	// Ignore has priority over all others (and is coded into bot, plugins only get called on normal
	// and above)
	enum Level
	{
		LEVEL_IGNORE,
		LEVEL_NORMAL,
		LEVEL_ADMIN
	};

	//
	/// \brief Returns a level from a given string
	//
	Level levelFromString (std::string string);

	//
	/// \brief Gets a string from a level
	//
	std::string stringFromLevel (Level level);

}

#endif // BOT_LEVEL_H
