//
/// \file plugins/wall/wall.h
/// \brief Wall plugin
//

#ifndef PLUGINS_WALL_WALL_H
#define PLUGINS_WALL_WALL_H

#include "../../bot/plugin.h"

class Wall : public JulieSu::Plugin
{
	public:
		void init (JulieSu::Bot* bot);
		void free (void);

		void run (JulieSu::Irc::Message message);
};

extern "C" JulieSu::Plugin* initPlugin (JulieSu::Bot* bot);
extern "C" void freePlugin (JulieSu::Plugin* plugin);

#endif // PLUGINS_WALL_WALL_H
