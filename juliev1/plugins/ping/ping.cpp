//
/// \file plugins/ping/ping.cpp
/// \brief Ping plugin
//

#include "ping.h"

void Ping::init (JulieSu::Bot* bot)
{
	this->author = "thothonegan";
	this->name = "Ping";
	this->description = "Plays PONG with the IRC server when bored";

	this->type = JulieSu::PLUGIN_RAW;
	
	this->bot = bot;
}

void Ping::free (void)
{}

void Ping::run (JulieSu::Irc::Message message)
{
	// We're lazy : just respond
	bot->getConnection()->send ("PONG :" + message.data);
}


JulieSu::Plugin* initPlugin (JulieSu::Bot* bot)
{
	JulieSu::Plugin* temp = new Ping;
	temp->init (bot);

	return temp;
}

void freePlugin (JulieSu::Plugin* plugin)
{
	plugin->free();

	delete plugin;
}

