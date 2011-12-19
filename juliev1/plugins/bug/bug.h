//
/// \file plugins/bug/bug.h
/// \brief Bug plugin
//

#ifndef PLUGINS_BUG_BUG_H
#define PLUGINS_BUG_BUG_H

#include "../../bot/plugin.h"

class Bug : public JulieSu::Plugin
{
	public:
		void init (JulieSu::Bot* bot);
		void free (void);

		void run (JulieSu::Irc::Message message);
};

extern "C" JulieSu::Plugin* initPlugin (JulieSu::Bot* bot);
extern "C" void freePlugin (JulieSu::Plugin* plugin);

#endif // PLUGINS_BUG_BUG_H
