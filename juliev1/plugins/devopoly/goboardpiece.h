//
/// \file plugins/devopoly/goboardpiece.h
/// \brief Go board piece
//

#ifndef PLUGINS_DEVOPOLY_GOBOARDPIECE_H
#define PLUGINS_DEVOPOLY_GOBOARDPIECE_H

#include "boardpiece.h"

#include "devopoly.h"

class DevopolyGoBoardPiece : public DevopolyBoardPiece
{
	public:
		//
		/// \brief Create the piece
		/// \param name The name of the piece
		/// \param plugin The devopoly plugin
		//
		DevopolyGoBoardPiece (std::string name, Devopoly* plugin);

		//
		/// \brief Return the piece's type (action)
		//
		DevopolyBoardPieceType getType (void) { return DEVOPOLY_BOARD_PIECE_TYPE_INSTANT; };

		//
		/// \brief Perform the piece's action on a player
		/// \param player The player to perform the action on
		/// \param players The rest of the players
		//
		void perform (DevopolyPlayer* player, std::vector<DevopolyPlayer>* players);
};

#endif // PLUGINS_DEVOPOLY_GOBOARDPIECE_H

