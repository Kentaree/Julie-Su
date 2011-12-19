//
/// \file plugins/devopoly/boardpiece.h
/// \brief A board piece
//

#ifndef PLUGINS_DEVOPOLY_BOARDPIECE_H
#define PLUGINS_DEVOPOLY_BOARDPIECE_H

#include "boardpiecetypes.h"
#include "player.h"
#include <vector>

class Devopoly;

class DevopolyBoardPiece
{
	public:
		//
		/// \brief Create the piece
		/// \param name The name of the piece
		/// \param plugin The plugin we are a part of
		//
		DevopolyBoardPiece (std::string name, Devopoly* plugin);

		//
		/// \brief Get the name of the piece
		//
		std::string getName (void);

		//
		/// \brief Get the type of piece
		//
		virtual DevopolyBoardPieceType getType () = 0;

		//
		/// \brief Perform the actions of the piece on a given player (only valid if type is INSTANT)
		/// \param player The current player
		/// \param players The list of all players
		//
		virtual void perform (DevopolyPlayer* player, std::vector<DevopolyPlayer>* players) = 0;

	protected:
		//
		/// \brief The name of the piece
		//
		std::string name;

		//
		/// \brief The devopoly plugin
		//
		Devopoly* plugin;
};

#endif // PLUGINS_DEVOPOLY_BOARDPIECE_H

