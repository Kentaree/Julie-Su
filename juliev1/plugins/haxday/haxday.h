//
/// \file plugins/haxday/haxday.h
/// \brief HaxDay plugin
//

#ifndef PLUGINS_HAXDAY_HAXDAY_H
#define PLUGINS_HAXDAY_HAXDAY_H

#include "../../bot/plugin.h"

#include <vector>
#include <string>

class HaxDay : public JulieSu::Plugin
{
	public:
		void init (JulieSu::Bot* bot);
		void free (void);

		void run (JulieSu::Irc::Message message);

	protected:
		//
		/// \brief Our list of people we've said hi to
		//
		std::vector<std::string> people;
};

extern "C" JulieSu::Plugin* initPlugin (JulieSu::Bot* bot);
extern "C" void freePlugin (JulieSu::Plugin* plugin);

#endif // PLUGINS_HAXDAY_HAXDAY_H
