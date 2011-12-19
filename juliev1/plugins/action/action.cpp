//
/// \file plugins/action/action.cpp
/// \brief Action plugin
//

#include "action.h"

void Action::init (JulieSu::Bot* bot)
{
	this->author = "thothonegan";
	this->name = "Action";
	this->description = "Tells JS to perform an action";

	this->type = JulieSu::PLUGIN_PRIVMSG;
	
	this->bot = bot;
}

void Action::free (void)
{}

void Action::run (JulieSu::Irc::Message message)
{
	// Respond to their message
	std::string response = message.privmsg_msg;
	response = response.substr(response.find(" ")+1);
	response.insert(0, "\001ACTION ");
	response += '\001';

	if (message.privmsg_target == bot->getName())
		bot->getConnection()->sendPrivMsg (message.nick, response);
	else
		bot->getConnection()->sendPrivMsg (message.privmsg_target, response);
}


JulieSu::Plugin* initPlugin (JulieSu::Bot* bot)
{
	JulieSu::Plugin* temp = new Action;
	temp->init (bot);

	return temp;
}

void freePlugin (JulieSu::Plugin* plugin)
{
	plugin->free();

	delete plugin;
}

