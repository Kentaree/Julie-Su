//
/// \file plugins/spell/spell.cpp
/// \brief Spell plugin
//

#include "spell.h"

#include <fstream>
#include <cstdlib>

#define SPELL_SCRIPT "../scripts/spell.rb"

void Spell::init (JulieSu::Bot* bot)
{
	this->author = "thothonegan";
	this->name = "Spell";
	this->description = "Corrects spelling mistakes";

	this->type = JulieSu::PLUGIN_PRIVMSG;
	
	this->bot = bot;
}

void Spell::free (void)
{}

void Spell::run (JulieSu::Irc::Message message)
{
	// Respond to their message
	std::string arguments = message.privmsg_msg;
	arguments = arguments.substr(arguments.find(" ")+1);

	while (arguments.find("\\0") != std::string::npos)
		arguments.erase (arguments.find("\\0"), 2);

	while (arguments.find("%") != std::string::npos)
		arguments.erase (arguments.find("%"), 1);

	while (arguments.find("'") != std::string::npos)
		arguments.erase (arguments.find("'"), 1);

	// Now lets run our script
	std::string tmp = SPELL_SCRIPT; tmp += " '"; tmp += arguments; tmp += "'"; tmp += " >output.txt";
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

	if (message.privmsg_target == bot->getName())
		bot->getConnection()->sendPrivMsg (message.nick, "[spell] " + line);
	else
		bot->getConnection()->sendPrivMsg (message.privmsg_target, "[spell] " + line);
}


JulieSu::Plugin* initPlugin (JulieSu::Bot* bot)
{
	JulieSu::Plugin* temp = new Spell;
	temp->init (bot);

	return temp;
}

void freePlugin (JulieSu::Plugin* plugin)
{
	plugin->free();

	delete plugin;
}

