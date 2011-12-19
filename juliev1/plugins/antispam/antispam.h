//
/// \file plugins/antispam/antispam.h
/// \brief AntiSpam plugin
//

#ifndef PLUGINS_ANTISPAM_ANTISPAM_H
#define PLUGINS_ANTISPAM_ANTISPAM_H

#include "../../bot/plugin.h"

#include <map>
#include <utility>
#include <string>

class AntiSpam : public JulieSu::Plugin
{
	public:
		void init (JulieSu::Bot* bot);
		void free (void);

		void run (JulieSu::Irc::Message message);

	protected:
		//
		/// \brief Our anti-spam map
		/// \note Format is <target, <"user:message", number_of_times_repeated> >
		//
		std::map <std::string, std::pair <std::string, int> > spammap; 
};

extern "C" JulieSu::Plugin* initPlugin (JulieSu::Bot* bot);
extern "C" void freePlugin (JulieSu::Plugin* plugin);

#endif // PLUGINS_ANTISPAM_ANTISPAM_H

