//
/// \file plugins/uptime/uptime.h
/// \brief Uptime plugin
//

#ifndef PLUGINS_UPTIME_UPTIME_H
#define PLUGINS_UPTIME_UPTIME_H

#include "../../bot/plugin.h"

class Uptime : public JulieSu::Plugin
{
	public:
		void init (JulieSu::Bot* bot);
		void free (void);

		void run (JulieSu::Irc::Message message);
};

extern "C" JulieSu::Plugin* initPlugin (JulieSu::Bot* bot);
extern "C" void freePlugin (JulieSu::Plugin* plugin);

#endif // PLUGINS_UPTIME_UPTIME_H
