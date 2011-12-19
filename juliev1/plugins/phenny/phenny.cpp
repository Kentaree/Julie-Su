//
/// \file plugins/phenny/phenny.cpp
/// \brief Phenny plugin
//

#include "phenny.h"

#include <cstdlib>
#include <fstream>
#include <string>
#include <iostream>

#define PHENNY_SCRIPT "../scripts/phenny.rb"
#define PHENNY_CACHE "phenny.cache"

#define MAX_MSG_LEN 500

void Phenny::init (JulieSu::Bot* bot)
{
	this->author = "thothonegan";
	this->name = "Phenny";
	this->description = "Talks with phenny services";

	this->type = JulieSu::PLUGIN_PRIVMSG;
	
	this->bot = bot;

	std::string cmd = PHENNY_SCRIPT;
	cmd += " " PHENNY_CACHE " Julie-Su refresh";
	system (cmd.c_str());
}

void Phenny::free (void)
{}

void Phenny::run (JulieSu::Irc::Message message)
{
	// Respond to their message
	std::string arguments = message.privmsg_msg;
	arguments = arguments.substr(arguments.find(" ")+1);

	// Prepare quotes
	for (int x=0; x < arguments.size(); ++x)
	{
		if (arguments[x] == '\"')
		{
			arguments.insert (arguments.begin()+x, '\\');
			x++;
		}
	}

	// Run script
	std::string command = PHENNY_SCRIPT;
	command += " " PHENNY_CACHE " " + message.nick + " " + arguments;
	command += " >output.txt";
	std::cout << "RUNNING : " << command << std::endl;
	system (command.c_str());

	// Now read the first line
	std::ifstream file ("output.txt");
	std::string line;
	getline (file, line);

	std::string msg = "[phenny] ";
	msg += line;

	if (msg.size() > MAX_MSG_LEN)
	{
		msg = msg.substr(0, MAX_MSG_LEN);

		msg += "[...]";
	}

	if (message.privmsg_target == bot->getName())
		bot->getConnection()->sendPrivMsg (message.nick, msg);
	else
		bot->getConnection()->sendPrivMsg (message.privmsg_target, msg);
}


JulieSu::Plugin* initPlugin (JulieSu::Bot* bot)
{
	JulieSu::Plugin* temp = new Phenny;
	temp->init (bot);

	return temp;
}

void freePlugin (JulieSu::Plugin* plugin)
{
	plugin->free();

	delete plugin;
}

