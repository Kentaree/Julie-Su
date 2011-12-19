//
/// \file plugins/zypper/zypper.cpp
/// \brief Zypper plugin
//

#include "zypper.h"

#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <sstream>

void Zypper::init (JulieSu::Bot* bot)
{
	this->author = "thothonegan";
	this->name = "Zypper";
	this->description = "Searches zypper for a given package";

	this->type = JulieSu::PLUGIN_PRIVMSG;
	
	this->bot = bot;
}

void Zypper::free (void)
{}

void Zypper::run (JulieSu::Irc::Message message)
{
	// Respond to their message
	std::string arguments = message.privmsg_msg;
	arguments = arguments.substr(arguments.find(" ")+1);

	std::string command = "zypper --no-refresh info '"; command += arguments; command += "' > output.txt";
	system (command.c_str());

	std::ifstream file ("output.txt");
	std::string line;

	std::string name;
	std::string version;
	std::string summary;

	getline (file, line);

	while (!file.bad() && !file.eof() && !file.fail())
	{
		if (line.find ("Name:") != std::string::npos)
		{
			name = line.substr (line.find(":") + 2);
		}

		if (line.find ("Version:") != std::string::npos)
		{
			version = line.substr (line.find(":") + 2);
		}

		if (line.find ("Summary:") != std::string::npos)
		{
			summary = line.substr (line.find(":") + 2);
		}

		getline (file, line);
	}

	file.close();

	std::stringstream str;
	str << "[zypper] " << name << " : " << version << " : " << summary;

	if (message.privmsg_target == bot->getName())
		bot->getConnection()->sendPrivMsg (message.nick, str.str());
	else
		bot->getConnection()->sendPrivMsg (message.privmsg_target, str.str());
}


JulieSu::Plugin* initPlugin (JulieSu::Bot* bot)
{
	JulieSu::Plugin* temp = new Zypper;
	temp->init (bot);

	return temp;
}

void freePlugin (JulieSu::Plugin* plugin)
{
	plugin->free();

	delete plugin;
}

