//
/// \file plugins/dice/source/dice.cc
/// \brief Dice plugin for JulieSu
//

#include "dice.h"
#include <cmath>
#include <ctime>

void Dice::Init (JulieSu::Irc::Connection* connection)
{
	this->author = "thothonegan";
	this->name = "Dice Plugin";

	this->connection = connection;

	srand (time(NULL));
}

void Dice::Free (void)
{
}

#include <iostream>
#include <sstream>
#include <string>
void Dice::Run (std::string arguments, JulieSu::Irc::Message message)
{
	// Parse
	// Formats
	// xdy
	// xdy+z
	// X is number of dice
	// Y is type of dice
	// Z is extra to add

	std::string amount;
	std::string type;
	std::string extra;

	int mode = 0; // 0 == looking for d, 1 == looking for +, 2 == rest

	for (int x=0; x < arguments.length(); ++x)
	{

		if (mode == 0)
		{
			// First, grab the first part as a number till we hit d or end of string
			if (arguments[x] != 'd')
			{
					amount += arguments[x];
			}
			else
			{
					// Hit a D, so we switch modes
					mode = 1;
			}
		}
		else if (mode == 1)
		{
			// Grab till we find plus or minus
			if (arguments[x] != '+' && arguments[x] != '-')
			{
				type += arguments[x];
			}
			else
			{
				// Hit a + or -, so we switch modes
				// If -, appen to beginning
				if (arguments[x] == '-')
				{
					std::string temp = type;
					type = "-";
					type += temp;
				}

				mode = 2;
			}
		}
		else if (mode == 2)
		{
			// Grab the extra part
			extra += arguments[x];
		}
	}

	int amount_num;
	int type_num;
	int extra_num;

	// Translate amount
	amount_num = atoi (amount.c_str());

	// Translate Type
	type_num = atoi (type.c_str());

	// Translate extra
	extra_num = atoi (extra.c_str());

	// Randomize
	int answer = 0;

	if (amount_num == 0)
		amount_num = 1;

	if (amount_num > 65535 || type_num > 65535)
	{
		if (connection->getNickname() == message.privmsg_target)
			connection->Send ("PRIVMSG " + message.nick + " :Use smaller numbers.");
		else
			connection->Send ("PRIVMSG " + message.privmsg_target + " :Use smaller numbers.");

	}

	for (int x=0; x < amount_num; ++x)
	{
		if (type_num != 0)
			answer += (rand () % type_num) + 1;
	}

	answer += extra_num;

	std::stringstream stream; stream << message.nick << " rolled a " << answer;

	if (connection->getNickname() == message.privmsg_target)
		connection->Send ("PRIVMSG " + message.nick + " :" + stream.str());
	else
		connection->Send ("PRIVMSG " + message.privmsg_target + " :" + stream.str());
}

JulieSu::Plugin* InitPlugin (JulieSu::Irc::Connection* connection)
{
	JulieSu::Plugin* temp = new Dice;
	temp->Init(connection);

	return temp;
}

void FreePlugin (JulieSu::Plugin* plugin)
{
	plugin->Free ();
	delete plugin;
}
