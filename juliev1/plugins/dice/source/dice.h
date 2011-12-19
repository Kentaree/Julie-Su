//
/// \file plugins/dice/source/dice.h
/// \brief Dice plugin for JulieSu
//

#ifndef PLUGINS_DICE_SOURCE_DICE_H
#define PLUGINS_DICE_SOURCE_DICE_H

#include "../../../bot/source/plugin.h"

class Dice : public JulieSu::Plugin
{
	public:
		void Init (JulieSu::Irc::Connection* connection);
		void Free (void);

		void Run (std::string arguments, JulieSu::Irc::Message message);
};

extern "C" JulieSu::Plugin* InitPlugin (JulieSu::Irc::Connection* connection);
extern "C" void FreePlugin (JulieSu::Plugin* plugin);

#endif // PLUGINS_DICE_SOURCE_DICE_H
