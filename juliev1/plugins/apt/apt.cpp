//
/// \file plugins/apt/apt.cpp
/// \brief Apt plugin
//

#include "apt.h"

#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <cstdlib>

void Apt::init (JulieSu::Bot* bot)
{
	this->author = "thothonegan";
	this->name = "Apt";
	this->description = "Searches apt for a given package";

	this->type = JulieSu::PLUGIN_PRIVMSG;
	
	this->bot = bot;
}

void Apt::free (void)
{}

void Apt::run (JulieSu::Irc::Message message)
{
	// Respond to their message
	std::string arguments = message.privmsg_msg;
	arguments = arguments.substr(arguments.find(" ")+1);

	std::string base_command = "apt-cache show '"; base_command += arguments; base_command += "'";

	// Grab the name, the version, and the description
	std::string command = base_command + " | grep 'Package' | sed 's/Package: //' | head -n1 > output.txt";
	system (command.c_str());

	command = base_command + " | grep 'Version' | sed 's/Version: //' | head -n1 >> output.txt";
	system (command.c_str());

	command = base_command + " | grep 'Description' | sed 's/Description: //' | head -n1 >> output.txt";
	system (command.c_str());

	std::ifstream file ("output.txt");

	std::string msg = "[apt] ";

	std::string line;

	// First is package name
	getline (file, line);
	msg += line;

	// Second is version
	getline (file, line);
	msg += " [" + line + "] ";

	// Last is description
	getline (file, line);
	msg += "- " + line;

	if (message.privmsg_target == bot->getName())
		bot->getConnection()->sendPrivMsg (message.nick, msg);
	else
		bot->getConnection()->sendPrivMsg (message.privmsg_target, msg);

	file.close();
}


JulieSu::Plugin* initPlugin (JulieSu::Bot* bot)
{
	JulieSu::Plugin* temp = new Apt;
	temp->init (bot);

	return temp;
}

void freePlugin (JulieSu::Plugin* plugin)
{
	plugin->free();

	delete plugin;
}

