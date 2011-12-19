//
/// \file plugins/youtube/youtube.h
/// \brief Youtube plugin
//

#ifndef PLUGINS_YOUTUBE_YOUTUBE_H
#define PLUGINS_YOUTUBE_YOUTUBE_H

#include "../../bot/plugin.h"

class Youtube : public JulieSu::Plugin
{
	public:
		void init (JulieSu::Bot* bot);
		void free (void);

		void run (JulieSu::Irc::Message message);
};

extern "C" JulieSu::Plugin* initPlugin (JulieSu::Bot* bot);
extern "C" void freePlugin (JulieSu::Plugin* plugin);

#endif // PLUGINS_YOUTUBE_YOUTUBE_H
