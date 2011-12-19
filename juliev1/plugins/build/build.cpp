//
/// \file plugins/build/build.cpp
/// \brief Build plugin
//

#include "build.h"

#include <cstdlib>
#include <fstream>

void Build::init (JulieSu::Bot* bot)
{
	this->author = "thothonegan";
	this->name = "Build";
	this->description = "Tells JS to rebuild herself (admin)";

	this->type = JulieSu::PLUGIN_PRIVMSG;
	
	this->bot = bot;
}

void Build::free (void)
{}

void Build::run (JulieSu::Irc::Message message)
{
	// Have to be an admin
	if (bot->getLevel (message.userhost) != JulieSu::LEVEL_ADMIN)
		return;

	std::string msgstr = "Rebuilding...";
	
	if (message.privmsg_target == bot->getName())
		bot->getConnection()->sendPrivMsg (message.nick, msgstr);
	else
		bot->getConnection()->sendPrivMsg (message.privmsg_target, msgstr);

	bool error = system ("make 2> tmp.txt");
	if (error != 0)
		msgstr = "Build error! (PMed)";
	else
		msgstr = "Build successful";

	if (message.privmsg_target == bot->getName())
		bot->getConnection()->sendPrivMsg (message.nick, msgstr);
	else
		bot->getConnection()->sendPrivMsg (message.privmsg_target, msgstr);

	// PM build stuff
	if (error)
	{
		std::ifstream output ("tmp.txt");

		while (!output.fail() && !output.bad() && !output.eof())
		{
			std::string cur_line;
			getline (output, cur_line);

			// Pm it
			bot->getConnection()->sendPrivMsg (message.nick, cur_line);
		}
	}
}


JulieSu::Plugin* initPlugin (JulieSu::Bot* bot)
{
	JulieSu::Plugin* temp = new Build;
	temp->init (bot);

	return temp;
}

void freePlugin (JulieSu::Plugin* plugin)
{
	plugin->free();

	delete plugin;
}

