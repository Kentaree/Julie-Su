//
/// \file plugins/devopoly/player.h
/// \brief A devopoly player
//

#ifndef PLUGINS_DEVOPOLY_PLAYER_H
#define PLUGINS_DEVOPOLY_PLAYER_H

#include <string>

class DevopolyPlayer
{
	public:
		//
		/// \brief Create a new player
		/// \param name The player's name
		//
		DevopolyPlayer (std::string name);

		//
		/// \brief Destroy the player
		//
		virtual ~DevopolyPlayer (void);

		//
		/// \brief Get the player's name
		//
		std::string getName (void);

		//
		/// \brief Get the amount of player's money
		//
		int getMoney (void);

		//
		/// \brief Set the amount of player's money
		/// \note Use getMoney() in combination to alter
		//
		void setMoney (int money);

		//
		/// \brief Get the current position of the player (board index)
		//
		unsigned int getPosition (void);

		//
		/// \brief Set the current position of the player (board index)
		//
		void setPosition (unsigned int position);

	protected:
		//
		/// \brief The player's name
		//
		std::string name;

		//
		/// \brief The amount of money they player has (bits)
		//
		int money;

		//
		/// \brief The current position of the player (index)
		//
		unsigned int position;
};

#endif // PLUGINS_DEVOPOLY_PLAYER_H

