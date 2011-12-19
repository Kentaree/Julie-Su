//
/// \file plugins/pizza/pizza.h
/// \brief Pizza plugin
//

#ifndef PLUGINS_PIZZA_PIZZA_H
#define PLUGINS_PIZZA_PIZZA_H

#include "../../bot/plugin.h"

class Pizza : public JulieSu::Plugin
{
	public:
		void init (JulieSu::Bot* bot);
		void free (void);

		void run (JulieSu::Irc::Message message);
};

extern "C" JulieSu::Plugin* initPlugin (JulieSu::Bot* bot);
extern "C" void freePlugin (JulieSu::Plugin* plugin);

#endif // PLUGINS_PIZZA_PIZZA_H
