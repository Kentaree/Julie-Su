//
/// \file plugins/map/map.h
/// \brief Map plugin
//

#ifndef PLUGINS_MAP_MAP_H
#define PLUGINS_MAP_MAP_H

#include "../../bot/plugin.h"

class Map : public JulieSu::Plugin
{
	public:
		void init (JulieSu::Bot* bot);
		void free (void);

		void run (JulieSu::Irc::Message message);
};

extern "C" JulieSu::Plugin* initPlugin (JulieSu::Bot* bot);
extern "C" void freePlugin (JulieSu::Plugin* plugin);

#endif // PLUGINS_MAP_MAP_H
