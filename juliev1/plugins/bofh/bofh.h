//
/// \file plugins/bofh/bofh.h
/// \brief BOFH plugin
//

#ifndef PLUGINS_BOFH_BOFH_H
#define PLUGINS_BOFH_BOFH_H

#include "../../bot/plugin.h"

class BOFH : public JulieSu::Plugin
{
	public:
		void init (JulieSu::Bot* bot);
		void free (void);

		void run (JulieSu::Irc::Message message);
};

extern "C" JulieSu::Plugin* initPlugin (JulieSu::Bot* bot);
extern "C" void freePlugin (JulieSu::Plugin* plugin);

#endif // PLUGINS_BOFH_BOFH_H
