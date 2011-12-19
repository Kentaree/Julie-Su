//
/// \file plugins/exec/exec.cpp
/// \brief Exec plugin
//

#include "exec.h"

#include <fstream>
#include <cstdlib>

void Exec::init (JulieSu::Bot* bot)
{
	this->author = "thothonegan";
	this->name = "Exec";
	this->description = "Runs arbitrary commands (admin)";

	this->type = JulieSu::PLUGIN_PRIVMSG;
	
	this->bot = bot;
}

void Exec::free (void)
{}

void Exec::run (JulieSu::Irc::Message message)
{
	// Respond to their message
	std::string arguments = message.privmsg_msg;
	arguments = arguments.substr(arguments.find(" ")+1);

	if (bot->getLevel (message.userhost) != JulieSu::LEVEL_ADMIN)
		return;

	// Exec the commanda
	std::string cmd = arguments + " > output.txt";
	system (cmd.c_str());

        // Now we read the first line of output.txt
        std::ifstream file ("output.txt");
        std::string line;
        getline (file, line);
        file.close();

        std::string msg = "[exec] " + line;

        if (message.privmsg_target == bot->getName())
                bot->getConnection()->sendPrivMsg (message.nick, msg);
        else
                bot->getConnection()->sendPrivMsg (message.privmsg_target, msg);

}


JulieSu::Plugin* initPlugin (JulieSu::Bot* bot)
{
	JulieSu::Plugin* temp = new Exec;
	temp->init (bot);

	return temp;
}

void freePlugin (JulieSu::Plugin* plugin)
{
	plugin->free();

	delete plugin;
}

