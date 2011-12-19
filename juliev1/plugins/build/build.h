//
/// \file plugins/build/build.h
/// \brief Build plugin
//

#ifndef PLUGINS_BUILD_BUILD_H
#define PLUGINS_BUILD_BUILD_H

#include "../../bot/plugin.h"

class Build : public JulieSu::Plugin
{
	public:
		void init (JulieSu::Bot* bot);
		void free (void);

		void run (JulieSu::Irc::Message message);
};

extern "C" JulieSu::Plugin* initPlugin (JulieSu::Bot* bot);
extern "C" void freePlugin (JulieSu::Plugin* plugin);

#endif // PLUGINS_BUILD_BUILD_H
