//
/// \file plugins/action/action.h
/// \brief Action plugin
//

#ifndef PLUGINS_ACTION_ACTION_H
#define PLUGINS_ACTION_ACTION_H

#include "../../bot/plugin.h"

class Action : public JulieSu::Plugin
{
	public:
		void init (JulieSu::Bot* bot);
		void free (void);

		void run (JulieSu::Irc::Message message);
};

extern "C" JulieSu::Plugin* initPlugin (JulieSu::Bot* bot);
extern "C" void freePlugin (JulieSu::Plugin* plugin);

#endif // PLUGINS_ACTION_ACTION_H
