//
/// \file plugins/apt/apt.h
/// \brief Apt plugin
//

#ifndef PLUGINS_APT_APT_H
#define PLUGINS_APT_APT_H

#include "../../bot/plugin.h"

class Apt : public JulieSu::Plugin
{
	public:
		void init (JulieSu::Bot* bot);
		void free (void);

		void run (JulieSu::Irc::Message message);
};

extern "C" JulieSu::Plugin* initPlugin (JulieSu::Bot* bot);
extern "C" void freePlugin (JulieSu::Plugin* plugin);

#endif // PLUGINS_APT_APT_H
