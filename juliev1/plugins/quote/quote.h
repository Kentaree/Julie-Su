//
/// \file plugins/quote/quote.h
/// \brief Echo plugin
//

#ifndef PLUGINS_QUOTE_QUOTE_H
#define PLUGINS_QUOTE_QUOTE_H

#include "../../bot/plugin.h"

class Quote : public JulieSu::Plugin
{
	public:
		void init (JulieSu::Bot* bot);
		void free (void);

		void run (JulieSu::Irc::Message message);
};

extern "C" JulieSu::Plugin* initPlugin (JulieSu::Bot* bot);
extern "C" void freePlugin (JulieSu::Plugin* plugin);

#endif // PLUGINS_QUOTE_QUOTE_H
