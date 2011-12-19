//
/// \file plugins/time/source/time.h
/// \brief Time plugin for JulieSu
//

#ifndef PLUGINS_TIME_SOURCE_TIME_H
#define PLUGINS_TIME_SOURCE_TIME_H

#include "../../../bot/source/plugin.h"

class Time : public JulieSu::Plugin
{
	public:
		void Init (JulieSu::Irc::Connection* connection);
		void Free (void);

		void Run (std::string arguments, JulieSu::Irc::Message message);
};

extern "C" JulieSu::Plugin* InitPlugin (JulieSu::Irc::Connection* connection);
extern "C" void FreePlugin (JulieSu::Plugin* plugin);

#endif // PLUGINS_TIME_SOURCE_TIME_H
