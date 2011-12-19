//
/// \file plugins/version/version.cpp
/// \brief Version plugin
//

#include "version.h"

void Version::init (JulieSu::Bot* bot)
{
	this->author = "thothonegan";
	this->name = "Version";
	this->description = "Returns JS version to a client";

	this->type = JulieSu::PLUGIN_CTCP;
	
	this->bot = bot;
}

void Version::free (void)
{}

void Version::run (JulieSu::Irc::Message message)
{
	// Respond to their message
	std::string arguments = message.privmsg_msg;
	arguments = arguments.substr(arguments.find(" ")+1);

	bot->getConnection()->sendCtcpResponse (message.nick, "VERSION Julie-Su Bot V 0.03 - Created by thothonegan");
}


JulieSu::Plugin* initPlugin (JulieSu::Bot* bot)
{
	JulieSu::Plugin* temp = new Version;
	temp->init (bot);

	return temp;
}

void freePlugin (JulieSu::Plugin* plugin)
{
	plugin->free();

	delete plugin;
}

