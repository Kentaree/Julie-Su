//
/// \file plugins/raw/source/raw.cc
/// \brief Raw plugin for JulieSu
//

#include "raw.h"

void Raw::Init (JulieSu::Irc::Connection* connection)
{
	this->author = "thothonegan";
	this->name = "Raw Plugin";

	this->connection = connection;
}

void Raw::Free (void)
{
}

#include <iostream>
void Raw::Run (std::string arguments, JulieSu::Irc::Message message)
{
	if(message.nick != "thothonegan")
		return;

	if (connection->getNickname() == message.privmsg_target)
		connection->Send (arguments);
	else
		connection->Send (arguments);
}

JulieSu::Plugin* InitPlugin (JulieSu::Irc::Connection* connection)
{
	JulieSu::Plugin* temp = new Raw;
	temp->Init(connection);

	return temp;
}

void FreePlugin (JulieSu::Plugin* plugin)
{
	plugin->Free ();
	delete plugin;
}
