//
/// \file plugins/portage/source/portage.cc
/// \brief Portage plugin for JulieSu
//

#include "portage.h"

void Portage::Init (JulieSu::Irc::Connection* connection)
{
	this->author = "thothonegan";
	this->name = "Portage Plugin";

	this->connection = connection;
}

void Portage::Free (void)
{
}

#include <iostream>
#include <string>
#include <fstream>

void Portage::Run (std::string arguments, JulieSu::Irc::Message message)
{
	std::string command = "eix -n -e -c "; command += arguments; command += " > output.txt";
	system (command.c_str());

	std::ifstream file ("output.txt");
	std::string line;

	getline (file, line);

	while (line != "")
	{
		while (line.find("[0m") != std::string::npos)
			line.erase (line.find("[0m"), strlen("[0m"));

		if (connection->getNickname() == message.privmsg_target)
			connection->Send ("PRIVMSG " + message.nick + " :" + line);
		else
			connection->Send ("PRIVMSG " + message.privmsg_target + " :" + line);

		getline (file, line);
	}
	file.close();

	/*
	getline (file, line);

	if (line == "No matches found.")
	{
		if (connection->getNickname() == message.privmsg_target)
			connection->Send ("PRIVMSG " + message.nick + " :" + line);
		else
			connection->Send ("PRIVMSG " + message.privmsg_target + " :" + line);
	}
	else
	{
			while (line.find("versions") == std::string::npos)
				getline (file, line);

			while (line.find("Installed") == std::string::npos &&
						 line.find("Homepage") == std::string::npos)
			{
				if (connection->getNickname() == message.privmsg_target)
					connection->Send ("PRIVMSG " + message.nick + " :" + line);
				else
					connection->Send ("PRIVMSG " + message.privmsg_target + " :" + line);

				getline (file, line);
			}
	}
	*/
}

JulieSu::Plugin* InitPlugin (JulieSu::Irc::Connection* connection)
{
	JulieSu::Plugin* temp = new Portage;
	temp->Init(connection);

	return temp;
}

void FreePlugin (JulieSu::Plugin* plugin)
{
	plugin->Free ();
	delete plugin;
}
