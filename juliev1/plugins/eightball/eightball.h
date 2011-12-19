//
/// \file plugins/eightball/eightball.h
/// \brief Eightball plugin
//

#ifndef PLUGINS_EIGHTBALL_EIGHTBALL_H
#define PLUGINS_EIGHTBALL_EIGHTBALL_H

#include "../../bot/plugin.h"

class EightBall : public JulieSu::Plugin
{
	public:
		void init (JulieSu::Bot* bot);
		void free (void);

		void run (JulieSu::Irc::Message message);
};

extern "C" JulieSu::Plugin* initPlugin (JulieSu::Bot* bot);
extern "C" void freePlugin (JulieSu::Plugin* plugin);

#endif // PLUGINS_EIGHTBALL_H
