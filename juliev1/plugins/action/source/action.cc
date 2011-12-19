//
/// \file plugins/action/source/action.cc
/// \brief Action plugin for JulieSu
//

#include "action.h"

void Action::Init (JulieSu::Irc::Connection* connection)
{
	this->author = "thothonegan";
	this->name = "Action Plugin";

	this->connection = connection;
}

void Action::Free (void)
{
}

#include <iostream>
void Action::Run (std::string arguments, JulieSu::Irc::Message message)
{
	std::string fullmsg = "\001ACTION" + arguments + "\001";
	if (connection->getNickname() == message.privmsg_target)
		connection->Send ("PRIVMSG " + message.nick + " :" + fullmsg);
	else
		connection->Send ("PRIVMSG " + message.privmsg_target + " :" + fullmsg);
}

JulieSu::Plugin* InitPlugin (JulieSu::Irc::Connection* connection)
{
	JulieSu::Plugin* temp = new Action;
	temp->Init(connection);

	return temp;
}

void FreePlugin (JulieSu::Plugin* plugin)
{
	plugin->Free ();
	delete plugin;
}
