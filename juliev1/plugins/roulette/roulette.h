//
/// \file plugins/roulette/roulette.h
/// \brief Roulette plugin
//

#ifndef PLUGINS_ROULETTE_ROULETTE_H
#define PLUGINS_ROULETTE_ROULETTE_H

#include "../../bot/plugin.h"

class Roulette : public JulieSu::Plugin
{
	public:
		void init (JulieSu::Bot* bot);
		void free (void);

		void run (JulieSu::Irc::Message message);
};

extern "C" JulieSu::Plugin* initPlugin (JulieSu::Bot* bot);
extern "C" void freePlugin (JulieSu::Plugin* plugin);

#endif // PLUGINS_ROULETTE_ROULETTE_H
