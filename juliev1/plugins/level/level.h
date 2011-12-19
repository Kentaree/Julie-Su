//
/// \file plugins/level/level.h
/// \brief Level plugin
//

#ifndef PLUGINS_LEVEL_LEVEL_H
#define PLUGINS_LEVEL_LEVEL_H

#include "../../bot/plugin.h"

class Level : public JulieSu::Plugin
{
	public:
		void init (JulieSu::Bot* bot);
		void free (void);

		void run (JulieSu::Irc::Message message);
};

extern "C" JulieSu::Plugin* initPlugin (JulieSu::Bot* bot);
extern "C" void freePlugin (JulieSu::Plugin* plugin);

#endif // PLUGINS_LEVEL_LEVEL_H

