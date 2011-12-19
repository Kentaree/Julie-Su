//
/// \file plugins/devopoly/goboardpiece.cpp
/// \brief Go board piece
//

#include "goboardpiece.h"

DevopolyGoBoardPiece::DevopolyGoBoardPiece (std::string name, Devopoly* plugin)
: DevopolyBoardPiece (name, plugin)
{}

void DevopolyGoBoardPiece::perform (DevopolyPlayer* player, std::vector<DevopolyPlayer>* players)
{
	plugin->sendMessage (player->getName() + " got 200 bits.");
	player->setMoney (player->getMoney() + 200);
}

