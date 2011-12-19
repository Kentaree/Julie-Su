//
/// \file plugins/raw/source/raw.h
/// \brief Raw plugin for JulieSu
//

#ifndef PLUGINS_RAW_SOURCE_RAW_H
#define PLUGINS_RAW_SOURCE_RAW_H

#include "../../../bot/source/plugin.h"

class Raw : public JulieSu::Plugin
{
	public:
		void Init (JulieSu::Irc::Connection* connection);
		void Free (void);

		void Run (std::string arguments, JulieSu::Irc::Message message);
};

extern "C" JulieSu::Plugin* InitPlugin (JulieSu::Irc::Connection* connection);
extern "C" void FreePlugin (JulieSu::Plugin* plugin);

#endif // PLUGINS_RAW_SOURCE_RAW_H
