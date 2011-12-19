//
/// \file plugins/userinfo/userinfo.h
/// \brief UserInfo plugin
//

#ifndef PLUGINS_USERINFO_USERINFO_H
#define PLUGINS_USERINFO_USERINFO_H

#include "../../bot/plugin.h"

class UserInfo : public JulieSu::Plugin
{
	public:
		void init (JulieSu::Bot* bot);
		void free (void);

		void run (JulieSu::Irc::Message message);
};

extern "C" JulieSu::Plugin* initPlugin (JulieSu::Bot* bot);
extern "C" void freePlugin (JulieSu::Plugin* plugin);

#endif // PLUGINS_USERINFO_USERINFO_H
