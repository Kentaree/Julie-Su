//
/// \file plugins/devopoly/boardpiece.cpp
/// \brief A single board piece
//

#include "boardpiece.h"

DevopolyBoardPiece::DevopolyBoardPiece (std::string name, Devopoly* plugin)
: name(name), plugin (plugin)
{}

std::string DevopolyBoardPiece::getName (void)
{
	return name;
}

