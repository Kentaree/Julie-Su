//
/// \file plugins/ping/ping.h
/// \brief Ping plugin
//

#ifndef PLUGINS_PING_PING_H
#define PLUGINS_PING_PING_H

#include "../../bot/plugin.h"

class Ping : public JulieSu::Plugin
{
	public:
		void init (JulieSu::Bot* bot);
		void free (void);

		void run (JulieSu::Irc::Message message);
};

extern "C" JulieSu::Plugin* initPlugin (JulieSu::Bot* bot);
extern "C" void freePlugin (JulieSu::Plugin* plugin);

#endif // PLUGINS_PING_PING_H

