//
/// \file plugins/help/help.h
/// \brief Help plugin
//

#ifndef PLUGINS_HELP_HELP_H
#define PLUGINS_HELP_HELP_H

#include "../../bot/plugin.h"

class Help : public JulieSu::Plugin
{
	public:
		void init (JulieSu::Bot* bot);
		void free (void);

		void run (JulieSu::Irc::Message message);

		void outputHTMLTo (std::string filename, std::string target);
};

extern "C" JulieSu::Plugin* initPlugin (JulieSu::Bot* bot);
extern "C" void freePlugin (JulieSu::Plugin* plugin);

#endif // PLUGINS_HELP_HELP_H
