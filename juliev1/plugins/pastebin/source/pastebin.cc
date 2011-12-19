//
/// \file plugins/pastebin/source/pastebin.cc
/// \brief Pastebin plugin for JulieSu
//

#include "pastebin.h"

void Pastebin::Init (JulieSu::Irc::Connection* connection)
{
	this->author = "thothonegan";
	this->name = "Pastebin Plugin";

	this->connection = connection;
}

void Pastebin::Free (void)
{
}

void Pastebin::Run (std::string arguments, JulieSu::Irc::Message message)
{
	std::string fullmsg;
	if (connection->getNickname() == message.privmsg_target)
		fullmsg = message.privmsg_target;
	else
		fullmsg = message.nick;

	fullmsg += " : http://pastebin.kentaree-studios.com";

	if (connection->getNickname() == message.privmsg_target)
		connection->Send ("PRIVMSG " + message.nick + " :" + fullmsg);
	else
		connection->Send ("PRIVMSG " + message.privmsg_target + " :" + fullmsg);
}

JulieSu::Plugin* InitPlugin (JulieSu::Irc::Connection* connection)
{
	JulieSu::Plugin* temp = new Pastebin;
	temp->Init(connection);

	return temp;
}

void FreePlugin (JulieSu::Plugin* plugin)
{
	plugin->Free ();
	delete plugin;
}
