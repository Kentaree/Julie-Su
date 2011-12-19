//
/// \file plugins/devhatdropbox/devhatdropbox.cpp
/// \brief Devhat Dropbox plugin
//

#include "devhatdropbox.h"

#include <iostream>
#include <cstring>
#include <cstdlib>

#define DIRECTORY "/home/thothonegan/Dropbox/Devhat"

void DevhatDropbox::init (JulieSu::Bot* bot)
{
	this->author = "thothonegan";
	this->name = "Devhat Dropbox";
	this->description = "Reports any changes to the Devhat Dropbox automatically";

	this->type = JulieSu::PLUGIN_PRIVMSG;
	
	this->bot = bot;

	// Setup our inotify watches
	inotifytools_initialize();

	int ret = inotifytools_watch_recursively (DIRECTORY,
		IN_MODIFY | IN_CREATE | IN_DELETE | IN_MOVE
	);

	if (!ret)
	{
		std::cout << "Couldnt watch : " << strerror (inotifytools_error()) << std::endl;
	}

}

void DevhatDropbox::free (void)
{
}

void DevhatDropbox::run (JulieSu::Irc::Message message)
{
	// Respond to their message
	std::string arguments = "This plugin runs automatically.";

	if (message.privmsg_target == bot->getName())
		bot->getConnection()->sendPrivMsg (message.nick, arguments);
	else
		bot->getConnection()->sendPrivMsg (message.privmsg_target, arguments);
}

void DevhatDropbox::loop (void)
{
	struct inotify_event* event = inotifytools_next_event (0);

	if (!event)
		if (inotifytools_error())
			std::cout << "Error : " << strerror(inotifytools_error() ) << std::endl;

	if (event)
	{
		last_event = time(NULL);

		std::cout << "Event! " << event->name << std::endl;

		if (event->len)
		{
			if (event_text == "")
				event_text = "[dropbox]";

			if (event->mask & IN_CREATE)
			{
				event_text += " : ";
				event_text += event->name;
				event_text += " Created";
			}

			else if (event->mask & IN_DELETE)
			{
				event_text += " : ";
				event_text += event->name;
				event_text += " Deleted";
			}

			else if (event->mask & IN_MODIFY)
			{
				event_text += " : ";
				event_text += event->name;
				event_text += " Modified";
			}

			else if (event->mask & IN_MOVE)
			{
				event_text += " : ";
				event_text += event->name;
				event_text += " Moved";
			}

		}

	}

	time_t cur_time = time(NULL);
	if (last_event + 5 < cur_time &&  event_text != "")
	{
		// Send the event text
		/// \todo Ask the plugin where its located and use that
		bot->getConnection()->sendPrivMsg ("#lobby", event_text);

		// Reset the event text
		event_text = "";
	}

}

JulieSu::Plugin* initPlugin (JulieSu::Bot* bot)
{
	JulieSu::Plugin* temp = new DevhatDropbox;
	temp->init (bot);

	return temp;
}

void freePlugin (JulieSu::Plugin* plugin)
{
	plugin->free();

	delete plugin;
}

