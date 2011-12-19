//
/// \file plugins/time/time.h
/// \brief Time plugin
//

#ifndef PLUGINS_TIME_TIME_H
#define PLUGINS_TIME_TIME_H

#include "../../bot/plugin.h"

class Time : public JulieSu::Plugin
{
	public:
		void init (JulieSu::Bot* bot);
		void free (void);

		void run (JulieSu::Irc::Message message);
};

extern "C" JulieSu::Plugin* initPlugin (JulieSu::Bot* bot);
extern "C" void freePlugin (JulieSu::Plugin* plugin);

#endif // PLUGINS_TIME_TIME_H
