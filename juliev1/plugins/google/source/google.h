//
/// \file plugins/google/source/dummy.h
/// \brief Google plugin for JulieSu
//

#ifndef PLUGINS_GOOGLE_SOURCE_GOOGLE_H
#define PLUGINS_GOOGLE_SOURCE_GOOGLE_H

#include "../../../bot/source/plugin.h"

#define GOOGLE_SCRIPT "../scripts/google.rb"

class Google : public JulieSu::Plugin
{
	public:
		void Init (JulieSu::Irc::Connection* connection);
		void Free (void);

		void Run (std::string arguments, JulieSu::Irc::Message message);
};

extern "C" JulieSu::Plugin* InitPlugin (JulieSu::Irc::Connection* connection);
extern "C" void FreePlugin (JulieSu::Plugin* plugin);

#endif // PLUGINS_GOOGLE_SOURCE_GOOGLE_H
