//
/// \file plugins/roulette/source/roulette.cc
/// \brief Roulette plugin for JulieSu
//

#include "roulette.h"

void Roulette::Init (JulieSu::Irc::Connection* connection)
{
	this->author = "thothonegan";
	this->name = "Roulette Plugin";

	this->connection = connection;
}

void Roulette::Free (void)
{
}

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>

#define CHAMBERS 6
#define BULLETS 1

bool chambers[CHAMBERS];

void Roulette::Run (std::string arguments, JulieSu::Irc::Message message)
{
	std::vector<std::string> deathmessages;
	deathmessages.push_back ("you are death!");
	deathmessages.push_back ("you are pregnant!");
	deathmessages.push_back ("EXPLOODIE!");
	deathmessages.push_back ("n00b! get out of here!");
	deathmessages.push_back ("See you in hell! But wait for me first!");

	std::vector<std::string> safemessages;
	safemessages.push_back ("safe for now");
	safemessages.push_back ("BOOM... only kidding");
	safemessages.push_back ("DIE ALREADY");
	safemessages.push_back ("enjoy life while you have it");

	if (arguments == " reset")
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

		if (connection->getNickname() == message.privmsg_target)
			connection->Send ("PRIVMSG " + message.nick + " :" + msg.str());
		else
			connection->Send ("PRIVMSG " + message.privmsg_target + " :" + msg.str());

		return;
	}

	if (arguments == " bullets")
	{
		int bullets_remaining = 0;
		for (int x=0; x < CHAMBERS; ++x)
		{
			if (chambers[x] == true)
				bullets_remaining++;
		}

		std::stringstream msg;
		msg << message.nick << ": There are " << bullets_remaining << " bullets remaining";

		if (connection->getNickname() == message.privmsg_target)
			connection->Send ("PRIVMSG " + message.nick + " :" + msg.str());
		else
			connection->Send ("PRIVMSG " + message.privmsg_target + " :" + msg.str());

		return;
	}

	// Spin the chamber
	int cham = rand() % CHAMBERS;

	if (chambers[cham] == true)
	{
		// Dead
		chambers[cham] = false;

		random_shuffle (deathmessages.begin(), deathmessages.end());

		std::string msg = message.nick + ": " + deathmessages[0];

		if (connection->getNickname() == message.privmsg_target)
			connection->Send ("PRIVMSG " + message.nick + " :" + msg);
		else
			connection->Send ("PRIVMSG " + message.privmsg_target + " :" + msg);

		std::string cmd = "KICK "; cmd += message.privmsg_target; cmd += " "; cmd += message.nick;
		cmd += " :"; cmd += msg;

		if (connection->getNickname() != message.privmsg_target)
			connection->Send (cmd.c_str());

	}
	else
	{
		random_shuffle (safemessages.begin(), safemessages.end());

		std::string msg = message.nick + ": " + safemessages[0];

		if (connection->getNickname() == message.privmsg_target)
			connection->Send ("PRIVMSG " + message.nick + " :" + msg);
		else
			connection->Send ("PRIVMSG " + message.privmsg_target + " :" + msg);

	}
}

JulieSu::Plugin* InitPlugin (JulieSu::Irc::Connection* connection)
{
	JulieSu::Plugin* temp = new Roulette;
	temp->Init(connection);

	return temp;
}

void FreePlugin (JulieSu::Plugin* plugin)
{
	plugin->Free ();
	delete plugin;
}
