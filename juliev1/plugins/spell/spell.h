//
/// \file plugins/spell/spell.h
/// \brief Spell plugin
//

#ifndef PLUGINS_SPELL_SPELL_H
#define PLUGINS_SPELL_SPELL_H

#include "../../bot/plugin.h"

class Spell : public JulieSu::Plugin
{
	public:
		void init (JulieSu::Bot* bot);
		void free (void);

		void run (JulieSu::Irc::Message message);
};

extern "C" JulieSu::Plugin* initPlugin (JulieSu::Bot* bot);
extern "C" void freePlugin (JulieSu::Plugin* plugin);

#endif // PLUGINS_SPELL_SPELL_H
