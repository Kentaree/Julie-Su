//
/// \file plugins/reload/reload.cpp
/// \brief Reload plugin
//

#include "reload.h"

#include "../../bot/global.h"

#include <iostream>

void Reload::init (JulieSu::Bot* bot)
{
	this->author = "thothonegan";
	this->name = "Reload";
	this->description = "Reloads JS (admin)";

	this->type = JulieSu::PLUGIN_PRIVMSG;
	
	this->bot = bot;
}

void Reload::free (void)
{}

void Reload::run (JulieSu::Irc::Message message)
{
	// Have to be an admin
	if (bot->getLevel (message.userhost) != JulieSu::LEVEL_ADMIN)
		return;

	std::string msgstr = "Reloading with same arguments...";
	
	if (message.privmsg_target == bot->getName())
		bot->getConnection()->sendPrivMsg (message.nick, msgstr);
	else
		bot->getConnection()->sendPrivMsg (message.privmsg_target, msgstr);

	bot->getConnection()->send ("QUIT :Reloading");

	// Fork us, and exit
	JulieSu::Output::write ("ARGV[0] : " + std::string(*JulieSu::argv));
	if (execvp (*JulieSu::argv, JulieSu::argv) < 0)
	{
		JulieSu::Output::write ("DEAD!");
	}

}


JulieSu::Plugin* initPlugin (JulieSu::Bot* bot)
{
	JulieSu::Plugin* temp = new Reload;
	temp->init (bot);

	return temp;
}

void freePlugin (JulieSu::Plugin* plugin)
{
	plugin->free();

	delete plugin;
}

