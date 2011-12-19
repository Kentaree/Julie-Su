//
/// \file plugins/log/log.cpp
/// \brief Log plugin
//

#include "log.h"

#include <iostream>

void Log::init (JulieSu::Bot* bot)
{
	this->author = "thothonegan";
	this->name = "Log";
	this->description = "logging data for stats : uses IRSSI format";

	this->type = JulieSu::PLUGIN_PRIVMSG;
	
	this->bot = bot;
}

void Log::free (void)
{}

void Log::run (JulieSu::Irc::Message message)
{
	// Write their message to the log
	if (logs.find (message.privmsg_target) == logs.end())
	{
		std::string filename = "logs/" + message.privmsg_target;
		std::cout << "[log] Starting log in " << filename << std::endl;

		// Open the log
		logs[message.privmsg_target] = new std::ofstream (filename.c_str(),
			std::ios_base::out | std::ios_base::app);

		time_t now = time (NULL);
		*(logs[message.privmsg_target]) << "--- Log opened " << ctime(&now) << std::endl;
	}

	// Add the message
	time_t cur = time (NULL);
	tm* t = gmtime (&cur);

	*(logs[message.privmsg_target])
		<< t->tm_hour << ":" << t->tm_min << " "
		"< " << message.nick << "> " << message.privmsg_msg << std::endl;
}


JulieSu::Plugin* initPlugin (JulieSu::Bot* bot)
{
	JulieSu::Plugin* temp = new Log;
	temp->init (bot);

	return temp;
}

void freePlugin (JulieSu::Plugin* plugin)
{
	plugin->free();

	delete plugin;
}

