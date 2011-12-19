//
/// \file plugins/roulette/roulette.cpp
/// \brief Roulette plugin
//

#include "roulette.h"

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>

#define CHAMBERS 6
#define BULLETS 1

bool chambers[CHAMBERS];

void Roulette::init (JulieSu::Bot* bot)
{
	this->author = "thothonegan";
	this->name = "Roulette";
	this->description = "Russian Roulette : do you feel lucky?";

	this->type = JulieSu::PLUGIN_PRIVMSG;
	
	this->bot = bot;
}

void Roulette::free (void)
{}

void Roulette::run (JulieSu::Irc::Message message)
{
	// Respond to their message
	std::string arguments = message.privmsg_msg;
	arguments = arguments.substr(arguments.find(" ")+1);

	std::vector<std::string> deathmessages;
	deathmessages.push_back ("you are death!");
	deathmessages.push_back ("you are pregnant!");
	deathmessages.push_back ("EXPLOODIE!");
	deathmessages.push_back ("n00b! get out of here!");
	deathmessages.push_back ("See you in hell! But wait for me first!");
	deathmessages.push_back ("You've turned into Vee!");
	deathmessages.push_back ("You have been eated by a grue!");

	std::vector<std::string> safemessages;
	safemessages.push_back ("safe for now");
	safemessages.push_back ("BOOM... only kidding");
	safemessages.push_back ("DIE ALREADY");
	safemessages.push_back ("enjoy life while you have it");

	if (arguments == "reset")
	{
		for (int x=0; x < CHAMBERS; ++x)
		{
			chambers[x] = false;
		}

		for (int x=0; x < BULLETS; ++x)
		{
			int cham = rand() % CHAMBERS;

			if (chambers[cham] == true)
			{
				--x;
			}
			else
			{
				chambers[cham] = true;
			}
		}

		std::stringstream msg;
		msg << message.nick << ": Reset with " << CHAMBERS << " chambers and " << BULLETS << " bullets";

		if (message.privmsg_target == bot->getName())
			bot->getConnection()->sendPrivMsg (message.nick, msg.str());
		else
			bot->getConnection()->sendPrivMsg (message.privmsg_target, msg.str());
		return;
	}

	if (arguments == "bullets")
	{
		int bullets_remaining = 0;
		for (int x=0; x < CHAMBERS; ++x)
		{
			if (chambers[x] == true)
				bullets_remaining++;
		}

		std::stringstream msg;
		msg << message.nick << ": There are " << bullets_remaining << " bullets remaining";

		if (message.privmsg_target == bot->getName())
			bot->getConnection()->sendPrivMsg (message.nick, msg.str());
		else
			bot->getConnection()->sendPrivMsg (message.privmsg_target, msg.str());
		return;
	}

	// Spin the chamber
	int cham = rand() % CHAMBERS;

	if (chambers[cham] == true)
	{
		// Dead
		chambers[cham] = false;

		random_shuffle (deathmessages.begin(), deathmessages.end());

		std::string msg = message.nick + ": [dead] " + deathmessages[0];

		if (message.privmsg_target == bot->getName())
			bot->getConnection()->sendPrivMsg (message.nick, msg);
		else
			bot->getConnection()->sendPrivMsg (message.privmsg_target, msg);

		std::string cmd = "KICK "; cmd += message.privmsg_target; cmd += " "; cmd += message.nick;
		cmd += " :"; cmd += msg;

		if (bot->getName() != message.privmsg_target)
			bot->getConnection()->send (cmd.c_str());

	}
	else
	{
		random_shuffle (safemessages.begin(), safemessages.end());

		std::string msg = message.nick + ": " + safemessages[0];

		if (message.privmsg_target == bot->getName())
			bot->getConnection()->sendPrivMsg (message.nick, msg);
		else
			bot->getConnection()->sendPrivMsg (message.privmsg_target, msg);

	}

}


JulieSu::Plugin* initPlugin (JulieSu::Bot* bot)
{
	JulieSu::Plugin* temp = new Roulette;
	temp->init (bot);

	return temp;
}

void freePlugin (JulieSu::Plugin* plugin)
{
	plugin->free();

	delete plugin;
}

