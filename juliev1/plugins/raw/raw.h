//
/// \file plugins/raw/raw.h
/// \brief Raw plugin
//

#ifndef PLUGINS_RAW_RAW_H
#define PLUGINS_RAW_RAW_H

#include "../../bot/plugin.h"

class Raw : public JulieSu::Plugin
{
	public:
		void init (JulieSu::Bot* bot);
		void free (void);

		void run (JulieSu::Irc::Message message);
};

extern "C" JulieSu::Plugin* initPlugin (JulieSu::Bot* bot);
extern "C" void freePlugin (JulieSu::Plugin* plugin);

#endif // PLUGINS_RAW_RAW_H
