//
/// \file plugins/ragepics/ragepics.cpp
/// \brief Ragepics plugin
//

#include "ragepics.h"

#include <cstdlib>
#include <fstream>
#include <string>
#include <iostream>

#define MEME_SCRIPT "../scripts/meme.rb"
#define MEME_CACHE "memes.cache"

#define MAX_MSG_LEN 500

void Ragepics::init (JulieSu::Bot* bot)
{
	this->author = "thothonegan + kentaree";
	this->name = "Ragepics";
	this->description = "Displays ragepic urls";

	this->type = JulieSu::PLUGIN_PRIVMSG;
	
	this->bot = bot;

	std::string cmd = MEME_SCRIPT;
	cmd += " " MEME_CACHE " Julie-Su refresh";
	system (cmd.c_str());
}

void Ragepics::free (void)
{}

void Ragepics::run (JulieSu::Irc::Message message)
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
	std::string command = MEME_SCRIPT;
	command += " " MEME_CACHE " " + arguments;
	command += " >output.txt";
	std::cout << "RUNNING : " << command << std::endl;
	system (command.c_str());

	// Now read the first line
	std::ifstream file ("output.txt");
	std::string line;
	getline (file, line);

	std::string msg = "[ragepics] ";
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
	JulieSu::Plugin* temp = new Ragepics;
	temp->init (bot);

	return temp;
}

void freePlugin (JulieSu::Plugin* plugin)
{
	plugin->free();

	delete plugin;
}

