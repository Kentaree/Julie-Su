//
/// \file plugins/quote/quote.cpp
/// \brief Quote plugin
//

#include "quote.h"

#include <fstream>
#include <cstdlib>

#define QUOTE_SCRIPT "../scripts/quote.rb"

void Quote::init (JulieSu::Bot* bot)
{
	this->author = "thothonegan";
	this->name = "Quote";
	this->description = "quote module - grabs quotes from devhat's quotedb";

	this->type = JulieSu::PLUGIN_PRIVMSG;
	
	this->bot = bot;
}

void Quote::free (void)
{}

void Quote::run (JulieSu::Irc::Message message)
{
	// Respond to their message
	std::string arguments = message.privmsg_msg + " ";
	arguments = arguments.substr(arguments.find(" ")+1);

	// Run the script
	std::string tmp = QUOTE_SCRIPT; tmp += " "; tmp += arguments; tmp += " >output.txt";
	system (tmp.c_str());

	// Read the result line
	std::ifstream file ("output.txt");
	std::string line;
	getline (file, line);

	std::string msg = "[quote] " + line;
	// Write the line
	if (message.privmsg_target == bot->getName())
		bot->getConnection()->sendPrivMsg (message.nick, msg);
	else
		bot->getConnection()->sendPrivMsg (message.privmsg_target, msg);
}


JulieSu::Plugin* initPlugin (JulieSu::Bot* bot)
{
	JulieSu::Plugin* temp = new Quote;
	temp->init (bot);

	return temp;
}

void freePlugin (JulieSu::Plugin* plugin)
{
	plugin->free();

	delete plugin;
}

