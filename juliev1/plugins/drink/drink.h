//
/// \file plugins/drink/drink.h
/// \brief Drink plugin
//

#ifndef PLUGINS_DRINK_DRINK_H
#define PLUGINS_DRINK_DRINK_H

#include "../../bot/plugin.h"

class Drink : public JulieSu::Plugin
{
	public:
		void init (JulieSu::Bot* bot);
		void free (void);

		void run (JulieSu::Irc::Message message);
};

extern "C" JulieSu::Plugin* initPlugin (JulieSu::Bot* bot);
extern "C" void freePlugin (JulieSu::Plugin* plugin);

#endif // PLUGINS_DRINK_DRINK_H
