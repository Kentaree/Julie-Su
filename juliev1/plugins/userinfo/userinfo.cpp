//
/// \file plugins/userinfo/userinfo.cpp
/// \brief UserInfo plugin
//

#include "userinfo.h"

void UserInfo::init (JulieSu::Bot* bot)
{
	this->author = "thothonegan";
	this->name = "UserInfo";
	this->description = "Returns UserInfo about JS for Kvirc and other clients";

	this->type = JulieSu::PLUGIN_CTCP;
	
	this->bot = bot;
}

void UserInfo::free (void)
{}

void UserInfo::run (JulieSu::Irc::Message message)
{
	// Respond to their message
	std::string arguments = message.privmsg_msg;
	arguments = arguments.substr(arguments.find(" ")+1);

	bot->getConnection()->sendCtcpResponse (message.nick, "USERINFO Age=0; Gender=Female; Location=Cyberspace; Languages=en; Ghost In The Machine");
}


JulieSu::Plugin* initPlugin (JulieSu::Bot* bot)
{
	JulieSu::Plugin* temp = new UserInfo;
	temp->init (bot);

	return temp;
}

void freePlugin (JulieSu::Plugin* plugin)
{
	plugin->free();

	delete plugin;
}

