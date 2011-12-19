//
/// \file plugins/roulette/source/roulette.h
/// \brief Roulette plugin for JulieSu
//

#ifndef PLUGINS_ROULETTE_SOURCE_ROULETTE_H
#define PLUGINS_ROULETTE_SOURCE_ROULETTE_H

#include "../../../bot/source/plugin.h"

class Roulette : public JulieSu::Plugin
{
	public:
		void Init (JulieSu::Irc::Connection* connection);
		void Free (void);

		void Run (std::string arguments, JulieSu::Irc::Message message);
};

extern "C" JulieSu::Plugin* InitPlugin (JulieSu::Irc::Connection* connection);
extern "C" void FreePlugin (JulieSu::Plugin* plugin);

#endif // PLUGINS_ROULETTE_SOURCE_ROULETTE_H
