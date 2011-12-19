//
/// \file plugins/drink/source/drink.cc
/// \brief Drink plugin for JulieSu
//

#include "drink.h"

void Drink::Init (JulieSu::Irc::Connection* connection)
{
	this->author = "thothonegan";
	this->name = "Drink Plugin";

	this->connection = connection;
}

void Drink::Free (void)
{
}

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

void Drink::Run (std::string arguments, JulieSu::Irc::Message message)
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

	if (connection->getNickname() == message.privmsg_target)
		connection->Send ("PRIVMSG " + message.nick + " :" + msg);
	else
		connection->Send ("PRIVMSG " + message.privmsg_target + " :" + msg);
}

JulieSu::Plugin* InitPlugin (JulieSu::Irc::Connection* connection)
{
	JulieSu::Plugin* temp = new Drink;
	temp->Init(connection);

	return temp;
}

void FreePlugin (JulieSu::Plugin* plugin)
{
	plugin->Free ();
	delete plugin;
}
