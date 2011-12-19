//
/// \file plugins/draw/stats.cpp
/// \brief Draw plugin
//

#include "draw.h"

#include <fstream>
#include <sstream>
#include <ctime>

void Draw::init (JulieSu::Bot* bot)
{
	this->author = "thothonegan";
	this->name = "Draw";
	this->description = "Shows the URL for the devhat flockdraw board";

	this->type = JulieSu::PLUGIN_PRIVMSG;
	
	this->bot = bot;
}

void Draw::free (void)
{
}

void Draw::run (JulieSu::Irc::Message message)
{
	std::string target = message.privmsg_target;

	std::string str = "[draw] http://flockdraw.com/devhat";

	if (message.privmsg_target == bot->getName())
		bot->getConnection()->sendPrivMsg (message.nick, str);
	else
		bot->getConnection()->sendPrivMsg (message.privmsg_target, str);
}

JulieSu::Plugin* initPlugin (JulieSu::Bot* bot)
{
	JulieSu::Plugin* temp = new Draw;
	temp->init (bot);

	return temp;
}

void freePlugin (JulieSu::Plugin* plugin)
{
	plugin->free();

	delete plugin;
}

