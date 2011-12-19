//
/// \file plugins/devopoly/propertyboardpiece.h
/// \brief Property board piece
//

#ifndef PLUGINS_DEVOPOLY_PROPERTYBOARDPIECE_H
#define PLUGINS_DEVOPOLY_PROPERTYBOARDPIECE_H

#include "boardpiece.h"

#include "devopoly.h"
#include "propertytypes.h"

class DevopolyPropertyBoardPiece : public DevopolyBoardPiece
{
	public:
		//
		/// \brief Create the piece
		/// \param name The name of the piece
		/// \param plugin The devopoly plugin
		/// \param type The type of piece this is
		//
		DevopolyPropertyBoardPiece (std::string name, Devopoly* plugin, DevopolyPropertyType type);

		//
		/// \brief Return the piece's type (action)
		//
		DevopolyBoardPieceType getType (void) { return DEVOPOLY_BOARD_PIECE_TYPE_PROPERTY; };

		//
		/// \brief Perform the piece's action on a player
		/// \param player The player to perform the action on
		/// \param players The rest of the players
		/// \note Does nothing for properties
		//
		void perform (DevopolyPlayer* player, std::vector<DevopolyPlayer>* players);

		//
		/// \brief Get the current value based on the number of houses
		//
		int getCurrentValue (void);

		//
		/// \brief Set the owner of this property
		//
		void setOwner (std::string owner);

		//
		/// \brief Get the owner of this property
		//
		std::string getOwner (void);

		//
		/// \brief Get the price of the property
		//
		int getPrice (void);

	protected:
		//
		/// \brief Our property type
		//
		DevopolyPropertyType type;

		//
		/// \brief The price to buy
		//
		int price;

		//
		/// \brief The rent value of this piece at certain hotel levels (0 through 5)
		//
		std::vector<int> rent;

		//
		/// \brief the number of hosues
		//
		int houses;

		//
		/// \brief Our owner
		//
		std::string owner;
};

#endif // PLUGINS_DEVOPOLY_GOBOARDPIECE_H

