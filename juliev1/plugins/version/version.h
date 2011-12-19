//
/// \file plugins/version/version.h
/// \brief Version plugin
//

#ifndef PLUGINS_VERSION_VERSION_H
#define PLUGINS_VERSION_VERSION_H

#include "../../bot/plugin.h"

class Version : public JulieSu::Plugin
{
	public:
		void init (JulieSu::Bot* bot);
		void free (void);

		void run (JulieSu::Irc::Message message);
};

extern "C" JulieSu::Plugin* initPlugin (JulieSu::Bot* bot);
extern "C" void freePlugin (JulieSu::Plugin* plugin);

#endif // PLUGINS_VERSION_VERSION_H
