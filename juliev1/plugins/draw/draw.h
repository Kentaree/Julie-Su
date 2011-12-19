//
/// \file plugins/draw/draw.h
/// \brief Draw plugin
//

#ifndef PLUGINS_DRAW_DRAW_H
#define PLUGINS_DRAW_DRAW_H

#include "../../bot/plugin.h"

class Draw : public JulieSu::Plugin
{
	public:
		void init (JulieSu::Bot* bot);
		void free (void);

		void run (JulieSu::Irc::Message message);

	protected:
};

extern "C" JulieSu::Plugin* initPlugin (JulieSu::Bot* bot);
extern "C" void freePlugin (JulieSu::Plugin* plugin);

#endif // PLUGINS_DRAW_DRAW_H
