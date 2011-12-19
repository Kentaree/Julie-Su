//
/// \file plugins/level/level.cpp
/// \brief Level plugin
//

#include "level.h"

#include <iostream>
#include <cstdlib>
#include <cstring>

void Level::init (JulieSu::Bot* bot)
{
	this->author = "thothonegan";
	this->name = "Level";
	this->description = "Manages user levels (admin)";

	this->type = JulieSu::PLUGIN_PRIVMSG;
	
	this->bot = bot;
}

void Level::free (void)
{}

void Level::run (JulieSu::Irc::Message message)
{
	// Respond to their message
	std::string arguments = message.privmsg_msg;
	arguments = arguments.substr(arguments.find(" ")+1);

	// Have to be an admin
	if (bot->getLevel (message.userhost) != JulieSu::LEVEL_ADMIN)
		return;

	// Now comes the parsing

	// We have three subcommands : set, remove, and help
	// Help is self explanatory
	// Set take two parameters : the mask and the level
	// Remove just needs the mask
	if (arguments == "help")
	{
		std::string target;

		if (message.privmsg_target == bot->getName())
			target = message.nick;
		else
			target = message.privmsg_target;

		bot->getConnection()->sendPrivMsg (target, "Usuage : [set <mask> <level>]");
		bot->getConnection()->sendPrivMsg (target, "Usuage : [remove <mask>]");
		bot->getConnection()->sendPrivMsg (target, "Usuage : [get <mask>]");
		bot->getConnection()->sendPrivMsg (target, "Usuage : [list <mask>]");
	}

	else if (arguments.substr (0, strlen("set")) == "set")
	{
		if (strlen("set") + 1 >= arguments.size())
			return; // stupid idiot

		arguments = arguments.substr (strlen("set") + 1);

		// find the next space
		int space = arguments.find (" ");

		std::string mask = arguments.substr (0, space);
		std::string level = arguments.substr (space+1);

		bot->setLevel (mask, JulieSu::levelFromString(level));
	}

	else if (arguments.substr (0, strlen("remove")) == "remove")
	{
		if (strlen("remove") + 1 >= arguments.size())
			return; // stupid idiot

		// One argument
		arguments = arguments.substr (strlen("remove") + 1);

		bot->removeLevel (arguments);
	}
	else if (arguments.substr (0, strlen("get")) == "get")
	{
		if (strlen("get") + 1 >= arguments.size())
			return; // stupid idiot

		// One argument
		arguments = arguments.substr (strlen("get") + 1);

		std::string level = stringFromLevel (bot->getLevel (arguments));

		std::string target;
		if (message.privmsg_target == bot->getName())
			target = message.nick;
		else
			target = message.privmsg_target;

		bot->getConnection()->sendPrivMsg (target, "Level for [" + arguments + "] : " + level);
	}

	else if (arguments.substr (0, strlen("list")) == "list")
	{
		// Get the list
		std::list <std::pair <std::string, JulieSu::Level> > levels = bot->getLevels();

		std::string target;

		if (message.privmsg_target == bot->getName())
			target = message.nick;
		else
			target = message.privmsg_target;

		// Now output the levels
		for (std::list<std::pair<std::string, JulieSu::Level> >::iterator iter = levels.begin(); iter != levels.end(); ++iter)
		{
			bot->getConnection()->sendPrivMsg (target, iter->first + " : " + stringFromLevel (iter->second));
		}
	}

}


JulieSu::Plugin* initPlugin (JulieSu::Bot* bot)
{
	JulieSu::Plugin* temp = new Level;
	temp->init (bot);

	return temp;
}

void freePlugin (JulieSu::Plugin* plugin)
{
	plugin->free();

	delete plugin;
}

