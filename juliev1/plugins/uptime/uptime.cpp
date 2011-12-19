//
/// \file plugins/uptime/uptime.cpp
/// \brief Uptime plugin
//

#include "uptime.h"

#include <cstdlib>
#include <fstream>

void Uptime::init (JulieSu::Bot* bot)
{
	this->author = "thothonegan";
	this->name = "Uptime";
	this->description = "Returns the uptime of JS and the system";

	this->type = JulieSu::PLUGIN_PRIVMSG;
	
	this->bot = bot;
}

void Uptime::free (void)
{}

void Uptime::run (JulieSu::Irc::Message message)
{
	// Respond to their message
	
	// Get the system uptime
	std::string tmp = "uptime"; tmp += " >output.txt";
	system (tmp.c_str());

	// Now we read the first line of output.txt
	std::ifstream file ("output.txt");
	std::string line;
	getline (file, line);
	file.close();

	std::string msg = "[uptime] [bot] " + bot->getUptime()  + " [system] " + line;

	if (message.privmsg_target == bot->getName())
		bot->getConnection()->sendPrivMsg (message.nick, msg);
	else
		bot->getConnection()->sendPrivMsg (message.privmsg_target, msg);
}


JulieSu::Plugin* initPlugin (JulieSu::Bot* bot)
{
	JulieSu::Plugin* temp = new Uptime;
	temp->init (bot);

	return temp;
}

void freePlugin (JulieSu::Plugin* plugin)
{
	plugin->free();

	delete plugin;
}

