//
/// \file plugins/pastebin/source/pastebin.h
/// \brief Pastebin plugin for JulieSu
//

#ifndef PLUGINS_PASTEBIN_SOURCE_PASTEBIN_H
#define PLUGINS_PASTEBIN_SOURCE_PASTEBIN_H

#include "../../../bot/source/plugin.h"

class Pastebin : public JulieSu::Plugin
{
	public:
		void Init (JulieSu::Irc::Connection* connection);
		void Free (void);

		void Run (std::string arguments, JulieSu::Irc::Message message);
};

extern "C" JulieSu::Plugin* InitPlugin (JulieSu::Irc::Connection* connection);
extern "C" void FreePlugin (JulieSu::Plugin* plugin);

#endif // PLUGINS_PASTEBIN_SOURCE_PASTEBIN_H
