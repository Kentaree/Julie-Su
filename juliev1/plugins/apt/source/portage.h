//
/// \file plugins/portage/source/dummy.h
/// \brief Portage plugin for JulieSu
//

#ifndef PLUGINS_PORTAGE_SOURCE_PORTAGE_H
#define PLUGINS_PORTAGE_SOURCE_PORTAGE_H

#include "../../../bot/source/plugin.h"

class Portage : public JulieSu::Plugin
{
	public:
		void Init (JulieSu::Irc::Connection* connection);
		void Free (void);

		void Run (std::string arguments, JulieSu::Irc::Message message);
};

extern "C" JulieSu::Plugin* InitPlugin (JulieSu::Irc::Connection* connection);
extern "C" void FreePlugin (JulieSu::Plugin* plugin);

#endif // PLUGINS_PORTAGE_SOURCE_PORTAGE_H
