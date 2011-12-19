//
/// \file plugins/stats/stats.cpp
/// \brief Stats plugin
//

#include "stats.h"

#include <fstream>
#include <sstream>
#include <ctime>

void Stats::init (JulieSu::Bot* bot)
{
	this->author = "thothonegan";
	this->name = "Stats";
	this->description = "Collects statistics on DevHat - also overrides !stats";

	this->type = JulieSu::PLUGIN_PRIVMSG;
	
	this->bot = bot;
}

void Stats::free (void)
{
}

void Stats::run (JulieSu::Irc::Message message)
{
	std::string target = message.privmsg_target;

	// Safe the target
	std::string safe_target = makeSafe (target);
	//std::string str = "[stats] http://www.hackerguild.com/juliesu/logs/" + safe_target + ".html";
	std::string str = "[stats] http://stats.devhat.net/";

	if (message.privmsg_target == bot->getName())
		bot->getConnection()->sendPrivMsg (message.nick, str);
	else
		bot->getConnection()->sendPrivMsg (message.privmsg_target, str);
}

std::string Stats::makeSafe (std::string str)
{
	std::string tempstr = str;
	// Replace #s
	while (tempstr.find ("#") != std::string::npos)
		tempstr.replace (tempstr.find("#"), 1, "");

	return tempstr;
}

JulieSu::Plugin* initPlugin (JulieSu::Bot* bot)
{
	JulieSu::Plugin* temp = new Stats;
	temp->init (bot);

	return temp;
}

void freePlugin (JulieSu::Plugin* plugin)
{
	plugin->free();

	delete plugin;
}

