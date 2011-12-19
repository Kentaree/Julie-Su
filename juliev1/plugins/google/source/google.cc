//
/// \file plugins/google/source/google.cc
/// \brief Google plugin for JulieSu
//

#include "google.h"
#include <fstream>

void Google::Init (JulieSu::Irc::Connection* connection)
{
	this->author = "thothonegan";
	this->name = "Google Plugin";

	this->connection = connection;

}

void Google::Free (void)
{
}

void Google::Run (std::string arguments, JulieSu::Irc::Message message)
{
	for (int x=0; x < arguments.size(); x++)
	{
		if ( arguments[x] < 32 || arguments[x] > 126)
		{
			arguments.erase(x, 1);
			x--;
		}
	}

	while (arguments.find("\\0") != std::string::npos)
		arguments.erase (arguments.find("\\0"), 2);

	while (arguments.find("%") != std::string::npos)
		arguments.erase (arguments.find("%"), 1);

	while (arguments.find("'") != std::string::npos)
		arguments.erase (arguments.find("'"), 1);

	// Google
/*
	if (arguments.find("google") != std::string::npos || arguments == "")
	{
		if (connection->getNickname() == message.privmsg_target)
			connection->Send ("PRIVMSG " + message.nick + " :[google] http://www.google.com (Google)");
		else
			connection->Send ("PRIVMSG " + message.privmsg_target + " :[google] http://www.google.com (Google)");

		return;
	}

	// Length
	else if (arguments.size() <= 3)
	{
		if (connection->getNickname() == message.privmsg_target)
			connection->Send ("PRIVMSG " + message.nick + " Google needs at least 4 characters for a query");
		else
			connection->Send ("PRIVMSG " + message.privmsg_target + " Google needs at least 4 characters for a query");

		return;
	}
*/
	// Now lets run our script
	std::string tmp = GOOGLE_SCRIPT; tmp += " '"; tmp += arguments; tmp += "'"; tmp += " >output.txt";
	system (tmp.c_str());

	// Now we read the first line of output.txt
	std::ifstream file ("output.txt");
	std::string line;
	getline (file, line);

	// Edit the line
	while (line.find("<b>") != std::string::npos)
		line.erase (line.find("<b>"), 3);

	while (line.find("</b>") != std::string::npos)
		line.erase (line.find("</b>"),4);

	while (line.find("<i>") != std::string::npos)
		line.erase (line.find("<i>"), 3);

	while (line.find("</i>") != std::string::npos)
		line.erase (line.find("</i>"), 4);

	while (line.find("<u>") != std::string::npos)
		line.erase (line.find("<u>"),  3);

	while (line.find("</u>") != std::string::npos)
		line.erase (line.find("</u>"), 4);

	// And we send it back
	if (connection->getNickname() == message.privmsg_target)
		connection->Send ("PRIVMSG " + message.nick + " :[google] " + line);
	else
		connection->Send ("PRIVMSG " + message.privmsg_target + " :[google] " + line);
}

JulieSu::Plugin* InitPlugin (JulieSu::Irc::Connection* connection)
{
	JulieSu::Plugin* temp = new Google;
	temp->Init(connection);

	return temp;
}

void FreePlugin (JulieSu::Plugin* plugin)
{
	plugin->Free ();
	delete plugin;
}
