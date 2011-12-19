//
/// \file plugins/action/source/action.h
/// \brief Action plugin for JulieSu
//

#ifndef PLUGINS_ACTION_SOURCE_ACTION_H
#define PLUGINS_ACTION_SOURCE_ACTION_H

#include "../../../bot/source/plugin.h"

class Action : public JulieSu::Plugin
{
	public:
		void Init (JulieSu::Irc::Connection* connection);
		void Free (void);

		void Run (std::string arguments, JulieSu::Irc::Message message);
};

extern "C" JulieSu::Plugin* InitPlugin (JulieSu::Irc::Connection* connection);
extern "C" void FreePlugin (JulieSu::Plugin* plugin);

#endif // PLUGINS_ACTION_SOURCE_ACTION_H
