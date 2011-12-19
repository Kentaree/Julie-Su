//
/// \file plugins/pastebin/pastebin.h
/// \brief Pastebin plugin
//

#ifndef PLUGINS_PASTEBIN_PASTEBIN_H
#define PLUGINS_PASTEBIN_PASTEBIN_H

#include "../../bot/plugin.h"

class Pastebin : public JulieSu::Plugin
{
	public:
		void init (JulieSu::Bot* bot);
		void free (void);

		void run (JulieSu::Irc::Message message);
};

extern "C" JulieSu::Plugin* initPlugin (JulieSu::Bot* bot);
extern "C" void freePlugin (JulieSu::Plugin* plugin);

#endif // PLUGINS_PASTEBIN_PASTEBIN_H
