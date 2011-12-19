//
/// \file plugins/avatar/avatar.h
/// \brief Avatar plugin
//

#ifndef PLUGINS_AVATAR_AVATAR_H
#define PLUGINS_AVATAR_AVATAR_H

#include "../../bot/plugin.h"

class Avatar : public JulieSu::Plugin
{
	public:
		void init (JulieSu::Bot* bot);
		void free (void);

		void run (JulieSu::Irc::Message message);
};

extern "C" JulieSu::Plugin* initPlugin (JulieSu::Bot* bot);
extern "C" void freePlugin (JulieSu::Plugin* plugin);

#endif // PLUGINS_AVATAR_AVATAR_H
