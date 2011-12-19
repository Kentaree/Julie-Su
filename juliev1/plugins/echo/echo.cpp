//
/// \file plugins/echo/echo.cpp
/// \brief Echo plugin
//

#include "echo.h"

void Echo::init (JulieSu::Bot* bot)
{
	this->author = "thothonegan";
	this->name = "Echo";
	this->description = "echo echo echo";

	this->type = JulieSu::PLUGIN_PRIVMSG;
	
	this->bot = bot;
}

void Echo::free (void)
{}

void Echo::run (JulieSu::Irc::Message message)
{
	// Respond to their message
	std::string arguments = message.privmsg_msg;
	arguments = arguments.substr(arguments.find(" ")+1);

	if (message.privmsg_target == bot->getName())
		bot->getConnection()->sendPrivMsg (message.nick, arguments);
	else
		bot->getConnection()->sendPrivMsg (message.privmsg_target, arguments);
}


JulieSu::Plugin* initPlugin (JulieSu::Bot* bot)
{
	JulieSu::Plugin* temp = new Echo;
	temp->init (bot);

	return temp;
}

void freePlugin (JulieSu::Plugin* plugin)
{
	plugin->free();

	delete plugin;
}

