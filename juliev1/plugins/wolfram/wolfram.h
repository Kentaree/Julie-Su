//
/// \file plugins/wolfram/wolfram.h
/// \brief Wolfram plugin
//

#ifndef PLUGINS_WOLFRAM_WOLFRAM_H
#define PLUGINS_WOLFRAM_WOLFRAM_H

#include "../../bot/plugin.h"

class Wolfram : public JulieSu::Plugin
{
	public:
		void init (JulieSu::Bot* bot);
		void free (void);

		void run (JulieSu::Irc::Message message);
};

extern "C" JulieSu::Plugin* initPlugin (JulieSu::Bot* bot);
extern "C" void freePlugin (JulieSu::Plugin* plugin);

#endif // PLUGINS_WOLFRAM_WOLFRAM_H
