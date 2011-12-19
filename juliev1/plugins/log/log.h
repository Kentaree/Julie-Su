//
/// \file plugins/log/log.h
/// \brief Log plugin
//

#ifndef PLUGINS_LOG_LOG_H
#define PLUGINS_LOG_LOG_H

#include "../../bot/plugin.h"

#include <map>
#include <string>
#include <fstream>

class Log : public JulieSu::Plugin
{
	public:
		void init (JulieSu::Bot* bot);
		void free (void);

		void run (JulieSu::Irc::Message message);

	protected:
		std::map<std::string, std::ofstream*> logs;
};

extern "C" JulieSu::Plugin* initPlugin (JulieSu::Bot* bot);
extern "C" void freePlugin (JulieSu::Plugin* plugin);

#endif // PLUGINS_LOG_LOG_H

