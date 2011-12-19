//
/// \file plugins/devhatdropbox/devhatdropbox.h
/// \brief Devhatdropbox plugin
//

#ifndef PLUGINS_ECHO_ECHO_H
#define PLUGINS_ECHO_ECHO_H

#include "../../bot/plugin.h"

#include <ctime>
#include <vector>

#include <inotifytools/inotifytools.h>
#include <inotifytools/inotify.h>

#define EVENT_SIZE ( sizeof (struct inotify_event) )
#define BUF_LEN (1024 * (EVENT_SIZE + 16 ) )

class DevhatDropbox : public JulieSu::Plugin
{
	public:
		void init (JulieSu::Bot* bot);
		void free (void);

		void run (JulieSu::Irc::Message message);
		void loop (void);

	protected:
		time_t last_event;
		std::string event_text;
};

extern "C" JulieSu::Plugin* initPlugin (JulieSu::Bot* bot);
extern "C" void freePlugin (JulieSu::Plugin* plugin);

#endif // PLUGINS_ECHO_ECHO_H
