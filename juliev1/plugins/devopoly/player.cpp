//
/// \file plugins/devopoly/player.cpp
/// \brief A devopoly player
//

#include "player.h"

DevopolyPlayer::DevopolyPlayer (std::string name)
: name (name), money (0)
{}

DevopolyPlayer::~DevopolyPlayer (void)
{}

std::string DevopolyPlayer::getName (void)
{
	return name;
}

int DevopolyPlayer::getMoney (void)
{
	return money;
}

void DevopolyPlayer::setMoney (int money)
{
	this->money = money;
}

unsigned int DevopolyPlayer::getPosition (void)
{
	return position;
}

void DevopolyPlayer::setPosition (unsigned int position)
{
	this->position = position;
}

