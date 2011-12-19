//
/// \file plugins/google/google.h
/// \brief Google plugin
//

#ifndef PLUGINS_GOOGLE_GOOGLE_H
#define PLUGINS_GOOGLE_GOOGLE_H

#include "../../bot/plugin.h"

class Google : public JulieSu::Plugin
{
	public:
		void init (JulieSu::Bot* bot);
		void free (void);

		void run (JulieSu::Irc::Message message);
};

extern "C" JulieSu::Plugin* initPlugin (JulieSu::Bot* bot);
extern "C" void freePlugin (JulieSu::Plugin* plugin);

#endif // PLUGINS_GOOGLE_GOOGLE_H
