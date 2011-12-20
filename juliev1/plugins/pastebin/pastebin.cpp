//
/// \file plugins/pastebin/pastebin.cpp
/// \brief Pastebin plugin
//

#include "pastebin.h"

void Pastebin::init (JulieSu::Bot* bot)
{
	this->author = "thothonegan";
	this->name = "Pastebin";
	this->description = "Returns the URL for the official devhat pastebin";

	this->type = JulieSu::PLUGIN_PRIVMSG;
	
	this->bot = bot;
}

void Pastebin::free (void)
{}

void Pastebin::run (JulieSu::Irc::Message message)
{
	// Respond to their message
        std::string msg = "[pastebin] http://pastebin.devhat.net"; //[pastebin] http://devhat.pastecode.com/";

	if (message.privmsg_target == bot->getName())
		bot->getConnection()->sendPrivMsg (message.nick, msg);
	else
		bot->getConnection()->sendPrivMsg (message.privmsg_target, msg);
}


JulieSu::Plugin* initPlugin (JulieSu::Bot* bot)
{
	JulieSu::Plugin* temp = new Pastebin;
	temp->init (bot);

	return temp;
}

void freePlugin (JulieSu::Plugin* plugin)
{
	plugin->free();

	delete plugin;
}

