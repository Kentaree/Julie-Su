//
/// \file plugins/phenny/phenny.h
/// \brief Phenny plugin
//

#ifndef PLUGINS_PHENNY_PHENNY_H
#define PLUGINS_PHENNY_PHENNY_H

#include "../../bot/plugin.h"

class Phenny : public JulieSu::Plugin
{
	public:
		void init (JulieSu::Bot* bot);
		void free (void);

		void refreshServices (void);

		void run (JulieSu::Irc::Message message);

	protected:
		//
		/// \brief Our services list
		/// \note Format is <key url>
		//
		std::map<std::string, std::string> services;
};

extern "C" JulieSu::Plugin* initPlugin (JulieSu::Bot* bot);
extern "C" void freePlugin (JulieSu::Plugin* plugin);

#endif // PLUGINS_PHENNY_PHENNY_H
