//
/// \file plugins/portage/portage.cpp
/// \brief Portage plugin
//

#include "portage.h"

#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <cstdlib>

void Portage::init (JulieSu::Bot* bot)
{
	this->author = "thothonegan";
	this->name = "Portage";
	this->description = "Searches portage for a given package";

	this->type = JulieSu::PLUGIN_PRIVMSG;
	
	this->bot = bot;
}

void Portage::free (void)
{}

void Portage::run (JulieSu::Irc::Message message)
{
	// Respond to their message
	std::string arguments = message.privmsg_msg;
	arguments = arguments.substr(arguments.find(" ")+1);

	std::string command = "eix -n -e -c '"; command += arguments; command += "' > output.txt";
	system (command.c_str());

	std::ifstream file ("output.txt");
	std::string line;

	getline (file, line);

	while (line != "")
	{
		while (line.find("[0m") != std::string::npos)
			line.erase (line.find("[0m"), strlen("[0m"));

	if (message.privmsg_target == bot->getName())
		bot->getConnection()->sendPrivMsg (message.nick, line);
	else
		bot->getConnection()->sendPrivMsg (message.privmsg_target, line);

		getline (file, line);
	}
	file.close();
}


JulieSu::Plugin* initPlugin (JulieSu::Bot* bot)
{
	JulieSu::Plugin* temp = new Portage;
	temp->init (bot);

	return temp;
}

void freePlugin (JulieSu::Plugin* plugin)
{
	plugin->free();

	delete plugin;
}

