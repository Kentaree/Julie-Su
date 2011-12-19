//
/// \file plugins/title/title.h
/// \brief Title plugin
//

#ifndef PLUGINS_TITLE_TITLE_H
#define PLUGINS_TITLE_TITLE_H

#include "../../bot/plugin.h"

class Title : public JulieSu::Plugin
{
	public:
		void init (JulieSu::Bot* bot);
		void free (void);

		void run (JulieSu::Irc::Message message);
};

extern "C" JulieSu::Plugin* initPlugin (JulieSu::Bot* bot);
extern "C" void freePlugin (JulieSu::Plugin* plugin);

#endif // PLUGINS_TITLE_TITLE_H
