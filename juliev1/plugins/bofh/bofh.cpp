//
/// \file plugins/bofh/bofh.cpp
/// \brief BOFH plugin
//

#include "bofh.h"

#include <cstdlib>
#include <fstream>

void BOFH::init (JulieSu::Bot* bot)
{
	this->author = "thothonegan";
	this->name = "BOFH";
	this->description = "Bastard Operator From Hell quotes";

	this->type = JulieSu::PLUGIN_PRIVMSG;
	
	this->bot = bot;
}

void BOFH::free (void)
{}

void BOFH::run (JulieSu::Irc::Message message)
{
	std::string command = "fortune bofh-excuses | awk '{ str1=str1 $0 " "}END{ print str1 }'";
	command += ">tmp.txt";
	system (command.c_str());

	// Now read the first line
	std::ifstream file ("tmp.txt");
	std::string line;
	getline (file, line);

	// Add our header
	std::string fullmsg = "[bofh] "; fullmsg += line;

	if (message.privmsg_target == bot->getName())
		bot->getConnection()->sendPrivMsg (message.nick, fullmsg);
	else
		bot->getConnection()->sendPrivMsg (message.privmsg_target, fullmsg);
}


JulieSu::Plugin* initPlugin (JulieSu::Bot* bot)
{
	JulieSu::Plugin* temp = new BOFH;
	temp->init (bot);

	return temp;
}

void freePlugin (JulieSu::Plugin* plugin)
{
	plugin->free();

	delete plugin;
}

