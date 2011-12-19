//
/// \file plugins/raw/raw.cpp
/// \brief Raw plugin
//

#include "raw.h"

void Raw::init (JulieSu::Bot* bot)
{
	this->author = "thothonegan";
	this->name = "Raw";
	this->description = "Sends raw commands to JS (admin)";

	this->type = JulieSu::PLUGIN_PRIVMSG;
	
	this->bot = bot;
}

void Raw::free (void)
{}

void Raw::run (JulieSu::Irc::Message message)
{
	// Respond to their message
	std::string arguments = message.privmsg_msg;
	arguments = arguments.substr(arguments.find(" ")+1);

	if (bot->getLevel (message.userhost) != JulieSu::LEVEL_ADMIN)
		return;

	bot->getConnection()->send (arguments);

}


JulieSu::Plugin* initPlugin (JulieSu::Bot* bot)
{
	JulieSu::Plugin* temp = new Raw;
	temp->init (bot);

	return temp;
}

void freePlugin (JulieSu::Plugin* plugin)
{
	plugin->free();

	delete plugin;
}

