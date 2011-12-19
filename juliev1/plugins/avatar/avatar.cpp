//
/// \file plugins/avatar/avatar.cpp
/// \brief Avatar plugin
//

#include "avatar.h"

void Avatar::init (JulieSu::Bot* bot)
{
	this->author = "thothonegan";
	this->name = "Avatar";
	this->description = "Sends avatar to Kvirc clients";

	this->type = JulieSu::PLUGIN_CTCP;
	
	this->bot = bot;
}

void Avatar::free (void)
{}

void Avatar::run (JulieSu::Irc::Message message)
{
	// Respond to their message
	std::string arguments = message.privmsg_msg;
	arguments = arguments.substr(arguments.find(" ")+1);

	bot->getConnection()->sendCtcpResponse (message.nick, "AVATAR http://dl.dropbox.com/u/170458/juliesu-avatar.png");
}


JulieSu::Plugin* initPlugin (JulieSu::Bot* bot)
{
	JulieSu::Plugin* temp = new Avatar;
	temp->init (bot);

	return temp;
}

void freePlugin (JulieSu::Plugin* plugin)
{
	plugin->free();

	delete plugin;
}

