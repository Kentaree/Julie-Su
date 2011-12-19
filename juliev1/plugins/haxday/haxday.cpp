//
/// \file plugins/haxday/haxday.cpp
/// \brief HaxDay plugin
//

#include "haxday.h"

#include <sstream>
#include <algorithm>

void HaxDay::init (JulieSu::Bot* bot)
{
	this->author = "thothonegan";
	this->name = "HaxDay";
	this->description = "Happy HaxDay!";

	this->type = JulieSu::PLUGIN_RAW;
	
	this->bot = bot;

}

void HaxDay::free (void)
{}

void HaxDay::run (JulieSu::Irc::Message message)
{
	// Respond to their message
	std::string arguments = message.privmsg_msg;
	arguments = arguments.substr(arguments.find(" ")+1);

	// Is it haxday?
	time_t t = time(NULL);
	tm* timeinfo = localtime (&t);
	
	if (timeinfo->tm_wday == 5) // Friday
	{
		// The channel is message.data
		std::string channel = message.data;
		std::string nick = message.nick;

		if (channel == "#help") /// \todo HACK Don't bother help
			return;

		std::stringstream str;

		if (std::find(people.begin(), people.end(), message.nick) == people.end())
		{
			str << "-=< Happy HaxDay ";
			if (nick != bot->getName())
			{
				str << nick << " ";
			}
			str << ">=-";
		
			bot->getConnection()->sendPrivMsg (channel, str.str());

			if (nick != bot->getName())
				people.push_back (nick);
		}
	}
	else
		people.clear();
}


JulieSu::Plugin* initPlugin (JulieSu::Bot* bot)
{
	JulieSu::Plugin* temp = new HaxDay;
	temp->init (bot);

	return temp;
}

void freePlugin (JulieSu::Plugin* plugin)
{
	plugin->free();

	delete plugin;
}

