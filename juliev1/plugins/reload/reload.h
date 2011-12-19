//
/// \file plugins/reload/reload.h
/// \brief Reload plugin
//

#ifndef PLUGINS_RELOAD_RELOAD_H
#define PLUGINS_RELOAD_RELOAD_H

#include "../../bot/plugin.h"

class Reload : public JulieSu::Plugin
{
	public:
		void init (JulieSu::Bot* bot);
		void free (void);

		void run (JulieSu::Irc::Message message);
};

extern "C" JulieSu::Plugin* initPlugin (JulieSu::Bot* bot);
extern "C" void freePlugin (JulieSu::Plugin* plugin);

#endif // PLUGINS_RELOAD_RELOAD_H
