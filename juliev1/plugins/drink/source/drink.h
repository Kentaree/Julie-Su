//
/// \file plugins/drink/source/drink.h
/// \brief Drink plugin for JulieSu
//

#ifndef PLUGINS_DRINK_SOURCE_DRINK_H
#define PLUGINS_DRINK_SOURCE_DRINK_H

#include "../../../bot/source/plugin.h"

class Drink : public JulieSu::Plugin
{
	public:
		void Init (JulieSu::Irc::Connection* connection);
		void Free (void);

		void Run (std::string arguments, JulieSu::Irc::Message message);
};

extern "C" JulieSu::Plugin* InitPlugin (JulieSu::Irc::Connection* connection);
extern "C" void FreePlugin (JulieSu::Plugin* plugin);

#endif // PLUGINS_DRINK_SOURCE_DRINK_H
