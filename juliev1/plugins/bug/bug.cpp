//
/// \file plugins/bug/bug.cpp
/// \brief Bug plugin
//

#include "bug.h"

void Bug::init (JulieSu::Bot* bot)
{
	this->author = "thothonegan";
	this->name = "Bug";
	this->description = "Bugzilla tracking";

	this->type = JulieSu::PLUGIN_PRIVMSG;
	
	this->bot = bot;
}

void Bug::free (void)
{}

void Bug::run (JulieSu::Irc::Message message)
{
	// Respond to their message
	std::string arguments = message.privmsg_msg;
	arguments = arguments.substr(arguments.find(" ")+1);

	std::string msg;
	if (arguments == "!bug")
		msg = "[bug] https://www.hackerguild.com/bugzilla/";
	else
	{
		arguments = arguments.substr (arguments.find(" ")+1);
		msg = "[bug] https://www.hackerguild.com/bugzilla/show_bug.cgi?id=" + arguments;
	}

	if (message.privmsg_target == bot->getName())
		bot->getConnection()->sendPrivMsg (message.nick, msg);
	else
		bot->getConnection()->sendPrivMsg (message.privmsg_target, msg);
}


JulieSu::Plugin* initPlugin (JulieSu::Bot* bot)
{
	JulieSu::Plugin* temp = new Bug;
	temp->init (bot);

	return temp;
}

void freePlugin (JulieSu::Plugin* plugin)
{
	plugin->free();

	delete plugin;
}

