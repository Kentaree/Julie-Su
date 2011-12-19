//
/// \file plugins/title/title.cpp
/// \brief Title plugin
//

#include "title.h"

#include <fstream>
#include <cstdlib>
#include <iostream>

#define TITLE_SCRIPT "../scripts/title.rb"

void Title::init (JulieSu::Bot* bot)
{
	this->author = "thothonegan";
	this->name = "Title";
	this->description = "Grabs the title of the given url";

	this->type = JulieSu::PLUGIN_PRIVMSG;
	
	this->bot = bot;
}

void Title::free (void)
{}

void Title::run (JulieSu::Irc::Message message)
{
	std::string arguments = message.data;

	// Find the link
	if (arguments.find("http://") == std::string::npos)
		return;
	
	arguments = arguments.substr (arguments.find("http://"));
	arguments = arguments.substr (0, arguments.find(" "));

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

	// Now lets run our script
	std::string tmp = TITLE_SCRIPT; tmp += " '"; tmp += arguments; tmp += "'"; tmp += " >output.txt";
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

	if (line == "")
		return;

	if (message.privmsg_target == bot->getName())
		bot->getConnection()->sendPrivMsg (message.nick, "[title] " + line);
	else
		bot->getConnection()->sendPrivMsg (message.privmsg_target, "[title] " + line);
}


JulieSu::Plugin* initPlugin (JulieSu::Bot* bot)
{
	JulieSu::Plugin* temp = new Title;
	temp->init (bot);

	return temp;
}

void freePlugin (JulieSu::Plugin* plugin)
{
	plugin->free();

	delete plugin;
}

