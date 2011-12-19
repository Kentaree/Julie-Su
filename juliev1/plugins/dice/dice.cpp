//
/// \file plugins/dice/dice.cpp
/// \brief Dice plugin
//

#include "dice.h"
#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <ctime>
#include <cstdlib>

void Dice::init (JulieSu::Bot* bot)
{
	this->author = "thothonegan";
	this->name = "Dice";
	this->description = "Rolls dice using D-notation ( 2d2+1 )";
	this->type = JulieSu::PLUGIN_PRIVMSG;
	
	this->bot = bot;
}

void Dice::free (void)
{}

void Dice::run (JulieSu::Irc::Message message)
{
	// Respond to their message
	std::string arguments = message.privmsg_msg;
	arguments = arguments.substr(arguments.find(" ")+1);

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

	if (type_num == 0)
		type_num = 6; // Default to d6

	// Randomize
	int answer = 0;

	if (amount_num == 0)
		amount_num = 1;

	if (amount_num > 65535 || type_num > 65535)
	{
		if (bot->getName() == message.privmsg_target)
			bot->getConnection()->sendPrivMsg (message.nick, "Use smaller numbers.");
		else
			bot->getConnection()->sendPrivMsg (message.privmsg_target, "Use smaller numbers.");
		return;
	}

	for (int x=0; x < amount_num; ++x)
	{
		if (type_num != 0)
			answer += (rand () % type_num) + 1;
	}

	answer += extra_num;

	std::stringstream stream; stream << "[" << amount_num << "d" << type_num << "+" << extra_num << "] " 
		<< message.nick << " rolled a " << answer;

	if (message.privmsg_target == bot->getName())
		bot->getConnection()->sendPrivMsg (message.nick, stream.str());
	else
		bot->getConnection()->sendPrivMsg (message.privmsg_target, stream.str());
}


JulieSu::Plugin* initPlugin (JulieSu::Bot* bot)
{
	JulieSu::Plugin* temp = new Dice;
	temp->init (bot);

	return temp;
}

void freePlugin (JulieSu::Plugin* plugin)
{
	plugin->free();

	delete plugin;
}

