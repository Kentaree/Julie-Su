//
/// \file plugins/devopoly/propertyboardpiece.cpp
/// \brief Property board piece
/// \note Numbers from http://en.wikibooks.org/wiki/Monopoly/Official_Rules
//

#include "propertyboardpiece.h"

#include <sstream>

DevopolyPropertyBoardPiece::DevopolyPropertyBoardPiece (std::string name, Devopoly* plugin, DevopolyPropertyType type)
: DevopolyBoardPiece (name, plugin), type (type), owner (""), houses(0)
{
	// Assign values
	switch (type)
	{
		case DEVOPOLY_PROPERTY_TYPE_PURPLE:
		{
			price = 60;

			// Rent prices
			rent.push_back (3);
			rent.push_back (15);
			rent.push_back (45);
			rent.push_back (135);
			rent.push_back (240);
			rent.push_back (350);

			break;
		}

		case DEVOPOLY_PROPERTY_TYPE_CYAN:
		{
			price = 170;

			// Rent prices
			rent.push_back (7);
			rent.push_back (0);
			rent.push_back (0);
			rent.push_back (0);
			rent.push_back (0);
			rent.push_back (0);

			break;
		}

		case DEVOPOLY_PROPERTY_TYPE_BROWN:
		{
			price = 147;

			// Rent prices
			rent.push_back (11);
			rent.push_back (0);
			rent.push_back (0);
			rent.push_back (0);
			rent.push_back (0);
			rent.push_back (0);

			break;
		}

		case DEVOPOLY_PROPERTY_TYPE_ORANGE:
		{
			price = 187;

			// Rent prices
			rent.push_back (15);
			rent.push_back (0);
			rent.push_back (0);
			rent.push_back (0);
			rent.push_back (0);
			rent.push_back (0);

			break;
		}

		case DEVOPOLY_PROPERTY_TYPE_RED:
		{
			price = 227;

			// Rent prices
			rent.push_back (19);
			rent.push_back (0);
			rent.push_back (0);
			rent.push_back (0);
			rent.push_back (0);
			rent.push_back (0);

			break;
		}

		case DEVOPOLY_PROPERTY_TYPE_YELLOW:
		{
			price = 267;

			// Rent prices
			rent.push_back (23);
			rent.push_back (0);
			rent.push_back (0);
			rent.push_back (0);
			rent.push_back (0);
			rent.push_back (0);

			break;
		}

		case DEVOPOLY_PROPERTY_TYPE_GREEN:
		{
			price = 307;

			// Rent prices
			rent.push_back (27);
			rent.push_back (0);
			rent.push_back (0);
			rent.push_back (0);
			rent.push_back (0);
			rent.push_back (0);

			break;
		}

		case DEVOPOLY_PROPERTY_TYPE_BLUE:
		{
			price = 375;

			// Rent prices
			rent.push_back (43);
			rent.push_back (0);
			rent.push_back (0);
			rent.push_back (0);
			rent.push_back (0);
			rent.push_back (0);

			break;
		}

		//RAILROAD

		//UTILITY
	}
}

void DevopolyPropertyBoardPiece::perform (DevopolyPlayer* player, std::vector<DevopolyPlayer>* players)
{
	// We're a property : display info, pay money etc
	if (owner == "")
	{
		std::stringstream s;
		s << "You can buy me for " << price << " bits";
		plugin->sendMessage (s.str());
	}
	else if (player->getName() == owner)
	{
		plugin->sendMessage ("You own this property :).");
	}
	else
	{
		int pay_rent = getCurrentValue();

		// Pay up!
		std::stringstream s;
		s << "Owned by " << owner << " : paid " << pay_rent << " in rent (" << houses << " houses)";
		plugin->sendMessage (s.str());

		player->setMoney (player->getMoney() - pay_rent);

		if (player->getMoney() < 0)
		{
			// Bye bye player
			plugin->sendMessage ("Out of money, bye bye");
			plugin->removePlayer (player->getName());
		}

		int owner_id = plugin->getPlayer (owner);
		(*players)[owner_id].setMoney ((*players)[owner_id].getMoney() + pay_rent);
	}
}

int DevopolyPropertyBoardPiece::getCurrentValue (void)
{
	return rent[houses];
}

void DevopolyPropertyBoardPiece::setOwner (std::string owner)
{
	this->owner = owner;
}

std::string DevopolyPropertyBoardPiece::getOwner (void)
{
	return owner;
}

int DevopolyPropertyBoardPiece::getPrice (void)
{
	return price;
}

