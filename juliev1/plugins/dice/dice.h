//
/// \file plugins/dice/dice.h
/// \brief Dice plugin
//

#ifndef PLUGINS_DICE_DICE_H
#define PLUGINS_DICE_DICE_H

#include "../../bot/plugin.h"

class Dice : public JulieSu::Plugin
{
	public:
		void init (JulieSu::Bot* bot);
		void free (void);

		void run (JulieSu::Irc::Message message);
};

extern "C" JulieSu::Plugin* initPlugin (JulieSu::Bot* bot);
extern "C" void freePlugin (JulieSu::Plugin* plugin);

#endif // PLUGINS_DICE_DICE_H
