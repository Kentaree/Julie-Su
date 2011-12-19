//
/// \file plugins/wall/wall.cpp
/// \brief Wall plugin
//

#include "wall.h"

void Wall::init (JulieSu::Bot* bot)
{
	this->author = "thothonegan";
	this->name = "Wall";
	this->description = "Sends a message to all of JS's channels (admin)";

	this->type = JulieSu::PLUGIN_PRIVMSG;
	
	this->bot = bot;
}

void Wall::free (void)
{}

void Wall::run (JulieSu::Irc::Message message)
{
	if (bot->getLevel (message.userhost) != JulieSu::LEVEL_ADMIN)
		return;

	std::string arguments = message.privmsg_msg;
	arguments = arguments.substr (arguments.find(" ")+1);

	std::string msg = "[wall] [" + message.nick + "] " + arguments;
 
	// Send to every channel
	std::vector<std::string> channels = bot->getChannels();

	for (unsigned int x=0; x < channels.size(); ++x)
	{
		bot->getConnection()->sendPrivMsg (channels[x], msg);
	}
}


JulieSu::Plugin* initPlugin (JulieSu::Bot* bot)
{
	JulieSu::Plugin* temp = new Wall;
	temp->init (bot);

	return temp;
}

void freePlugin (JulieSu::Plugin* plugin)
{
	plugin->free();

	delete plugin;
}

