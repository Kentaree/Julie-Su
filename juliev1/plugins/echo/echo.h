//
/// \file plugins/echo/echo.h
/// \brief Echo plugin
//

#ifndef PLUGINS_ECHO_ECHO_H
#define PLUGINS_ECHO_ECHO_H

#include "../../bot/plugin.h"

class Echo : public JulieSu::Plugin
{
	public:
		void init (JulieSu::Bot* bot);
		void free (void);

		void run (JulieSu::Irc::Message message);
};

extern "C" JulieSu::Plugin* initPlugin (JulieSu::Bot* bot);
extern "C" void freePlugin (JulieSu::Plugin* plugin);

#endif // PLUGINS_ECHO_ECHO_H
