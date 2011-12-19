//
/// \file plugins/drink/drink.cpp
/// \brief Drink plugin
//

#include "drink.h"

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

void Drink::init (JulieSu::Bot* bot)
{
	this->author = "thothonegan";
	this->name = "Drink";
	this->description = "Serves drinks. Enjoy";

	this->type = JulieSu::PLUGIN_PRIVMSG;
	
	this->bot = bot;
}

void Drink::free (void)
{}

void Drink::run (JulieSu::Irc::Message message)
{
	std::vector <std::string> drink;
	drink.push_back ("screwdriver");
	drink.push_back ("snakebite");
	drink.push_back ("sprite");
	drink.push_back ("coke");
	drink.push_back ("pepsi");
	drink.push_back ("bloody mary");
	drink.push_back ("pina coloda");
	drink.push_back ("margarita");
	drink.push_back ("sierra mist");
	drink.push_back ("blue balls");
	drink.push_back ("orange juice");
	drink.push_back ("water");
	drink.push_back ("cherry coke");
	drink.push_back ("cherry pepsi");
	drink.push_back ("mountain dew");
	drink.push_back ("rum");
	drink.push_back ("bawls");
	drink.push_back ("vodka");
	drink.push_back ("fake drink");
	drink.push_back ("root beer float");
	drink.push_back ("root beer");
	drink.push_back ("cream soda");
	drink.push_back ("prune juice");
	drink.push_back ("orange juice");
	drink.push_back ("salt water");
	drink.push_back ("strongbow cider");
	drink.push_back ("bong water");
	drink.push_back ("tiddles");
	drink.push_back ("dr pepper");
	drink.push_back ("battery acid");
	drink.push_back ("long island ice tea");

	random_shuffle (drink.begin(), drink.end());

	std::string msg = message.nick + " received a " + *drink.begin();

	if (message.privmsg_target == bot->getName())
		bot->getConnection()->sendPrivMsg (message.nick, msg);
	else
		bot->getConnection()->sendPrivMsg (message.privmsg_target, msg);
}


JulieSu::Plugin* initPlugin (JulieSu::Bot* bot)
{
	JulieSu::Plugin* temp = new Drink;
	temp->init (bot);

	return temp;
}

void freePlugin (JulieSu::Plugin* plugin)
{
	plugin->free();

	delete plugin;
}

