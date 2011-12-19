//
/// \file plugins/map/map.cpp
/// \brief Map plugin
//

#include "map.h"

void Map::init (JulieSu::Bot* bot)
{
	this->author = "thothonegan";
	this->name = "Map";
	this->description = "Returns the URL to the Devhat user map";

	this->type = JulieSu::PLUGIN_PRIVMSG;
	
	this->bot = bot;
}

void Map::free (void)
{}

void Map::run (JulieSu::Irc::Message message)
{
	// Respond to their message
	std::string arguments = message.privmsg_msg;
	arguments = arguments.substr(arguments.find(" ")+1);

	std::string msg = "[map] http://thothonegan.themoggie.co.uk/drupal/node/17";

	if (message.privmsg_target == bot->getName())
		bot->getConnection()->sendPrivMsg (message.nick, msg);
	else
		bot->getConnection()->sendPrivMsg (message.privmsg_target, msg);
}


JulieSu::Plugin* initPlugin (JulieSu::Bot* bot)
{
	JulieSu::Plugin* temp = new Map;
	temp->init (bot);

	return temp;
}

void freePlugin (JulieSu::Plugin* plugin)
{
	plugin->free();

	delete plugin;
}

