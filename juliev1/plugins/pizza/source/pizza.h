//
/// \file plugins/pizza/source/pizza.h
/// \brief Pizza plugin for JulieSu
//

#ifndef PLUGINS_PIZZA_SOURCE_PIZZA_H
#define PLUGINS_PIZZA_SOURCE_PIZZA_H

#include "../../../bot/source/plugin.h"

class Pizza : public JulieSu::Plugin
{
	public:
		void Init (JulieSu::Irc::Connection* connection);
		void Free (void);

		void Run (std::string arguments, JulieSu::Irc::Message message);
};

extern "C" JulieSu::Plugin* InitPlugin (JulieSu::Irc::Connection* connection);
extern "C" void FreePlugin (JulieSu::Plugin* plugin);

#endif // PLUGINS_PIZZA_SOURCE_PIZZA_H
