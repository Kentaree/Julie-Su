//
/// \file plugins/pizza/source/pizza.cc
/// \brief Pizza plugin for JulieSu
//

#include "pizza.h"

void Pizza::Init (JulieSu::Irc::Connection* connection)
{
	this->author = "thothonegan";
	this->name = "Pizza Plugin";

	this->connection = connection;
}

void Pizza::Free (void)
{
}

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

void Pizza::Run (std::string arguments, JulieSu::Irc::Message message)
{
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

	if (connection->getNickname() == message.privmsg_target)
		connection->Send ("PRIVMSG " + message.nick + " :" + msg);
	else
		connection->Send ("PRIVMSG " + message.privmsg_target + " :" + msg);
}

JulieSu::Plugin* InitPlugin (JulieSu::Irc::Connection* connection)
{
	JulieSu::Plugin* temp = new Pizza;
	temp->Init(connection);

	return temp;
}

void FreePlugin (JulieSu::Plugin* plugin)
{
	plugin->Free ();
	delete plugin;
}
