//
/// \file plugins/exec/exec.h
/// \brief Exec plugin
//

#ifndef PLUGINS_EXEC_EXEC_H
#define PLUGINS_EXEC_EXEC_H

#include "../../bot/plugin.h"

class Exec : public JulieSu::Plugin
{
	public:
		void init (JulieSu::Bot* bot);
		void free (void);

		void run (JulieSu::Irc::Message message);
};

extern "C" JulieSu::Plugin* initPlugin (JulieSu::Bot* bot);
extern "C" void freePlugin (JulieSu::Plugin* plugin);

#endif // PLUGINS_EXEC_EXEC_H
