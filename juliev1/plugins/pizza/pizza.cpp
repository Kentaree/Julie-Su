//
/// \file plugins/pizza/pizza.cpp
/// \brief Pizza plugin
//

#include "pizza.h"

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

void Pizza::init (JulieSu::Bot* bot)
{
	this->author = "thothonegan";
	this->name = "Pizza";
	this->description = "Free pizza for all!";

	this->type = JulieSu::PLUGIN_PRIVMSG;
	
	this->bot = bot;
}

void Pizza::free (void)
{}

void Pizza::run (JulieSu::Irc::Message message)
{
	// Respond to their message
	std::string arguments = message.privmsg_msg;
	arguments = arguments.substr(arguments.find(" ")+1);

	std::vector <std::string> pizza;

	pizza.push_back ("4 cheese pizza");
	pizza.push_back ("bullet pizza");
	pizza.push_back ("vodka sauce pizza");
	pizza.push_back ("fake pizza");
	pizza.push_back ("chicken bbq pizza");
	pizza.push_back ("extra cheese pizza");
	pizza.push_back ("veggie pizza");
	pizza.push_back ("pineapple and black olive pizza");
	pizza.push_back ("onion pizza");
	pizza.push_back ("brocolli pizza");
	pizza.push_back ("mushroom pizza");
	pizza.push_back ("bell pepper pizza");
	pizza.push_back ("french fry and ranch dressing pizza");
	pizza.push_back ("pepperoni pizza");

	random_shuffle (pizza.begin(), pizza.end());

	std::string msg = message.nick + " received a " + *pizza.begin();

	if (message.privmsg_target == bot->getName())
		bot->getConnection()->sendPrivMsg (message.nick, msg);
	else
		bot->getConnection()->sendPrivMsg (message.privmsg_target, msg);
}


JulieSu::Plugin* initPlugin (JulieSu::Bot* bot)
{
	JulieSu::Plugin* temp = new Pizza;
	temp->init (bot);

	return temp;
}

void freePlugin (JulieSu::Plugin* plugin)
{
	plugin->free();

	delete plugin;
}

