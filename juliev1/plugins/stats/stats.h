//
/// \file plugins/stats/stats.h
/// \brief Stats plugin
//

#ifndef PLUGINS_STATS_STATS_H
#define PLUGINS_STATS_STATS_H

#include "../../bot/plugin.h"

#include "sqlite/database.h"

class Stats : public JulieSu::Plugin
{
	public:
		void init (JulieSu::Bot* bot);
		void free (void);

		void run (JulieSu::Irc::Message message);

		std::string makeSafe (std::string str);

	protected:
};

extern "C" JulieSu::Plugin* initPlugin (JulieSu::Bot* bot);
extern "C" void freePlugin (JulieSu::Plugin* plugin);

#endif // PLUGINS_STATS_STATS_H
