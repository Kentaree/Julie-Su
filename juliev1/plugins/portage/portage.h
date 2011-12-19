//
/// \file plugins/portage/portage.h
/// \brief Portage plugin
//

#ifndef PLUGINS_PORTAGE_PORTAGE_H
#define PLUGINS_PORTAGE_PORTAGE_H

#include "../../bot/plugin.h"

class Portage : public JulieSu::Plugin
{
	public:
		void init (JulieSu::Bot* bot);
		void free (void);

		void run (JulieSu::Irc::Message message);
};

extern "C" JulieSu::Plugin* initPlugin (JulieSu::Bot* bot);
extern "C" void freePlugin (JulieSu::Plugin* plugin);

#endif // PLUGINS_PORTAGE_PORTAGE_H
