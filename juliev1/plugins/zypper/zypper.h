//
/// \file plugins/zypper/zypper.h
/// \brief Zypper plugin
//

#ifndef PLUGINS_ZYPPER_ZYPPER_H
#define PLUGINS_ZYPPER_ZYPPER_H

#include "../../bot/plugin.h"

class Zypper : public JulieSu::Plugin
{
	public:
		void init (JulieSu::Bot* bot);
		void free (void);

		void run (JulieSu::Irc::Message message);
};

extern "C" JulieSu::Plugin* initPlugin (JulieSu::Bot* bot);
extern "C" void freePlugin (JulieSu::Plugin* plugin);

#endif // PLUGINS_ZYPPER_ZYPPER_H
