//
/// \file plugins/devopoly/devopoly.h
/// \brief Devopoly plugin
//

#ifndef PLUGINS_DEVOPOLY_DEVOPOLY_H
#define PLUGINS_DEVOPOLY_DEVOPOLY_H

#include "../../bot/plugin.h"
#include "player.h"
#include "boardpiece.h"

#include <vector>
#include <algorithm>

enum DevopolyGameState
{
	DEVOPOLY_STATE_NONE, ///< No state, no game in progress
	DEVOPOLY_STATE_JOIN, ///< Waiting for players to join, host is chosen
	DEVOPOLY_STATE_PLAY ///< In the middle of playing a game
};

class Devopoly : public JulieSu::Plugin
{
	public:
		Devopoly (void) : current_message ("") {}

		void init (JulieSu::Bot* bot);
		void free (void);

		void run (JulieSu::Irc::Message message);

		void displayHelp (void); ///< Displays the currently available help

		void newGame (void); ///< Starts a new game
		void endGame (void); ///< End the current game (if host requested)
		void joinGame (void); ///< Join the current game
		void partGame (void); ///< Part the current game
		void kickPlayer (std::string player); ///< Kick a player from the current game (if host requested)
		void removePlayer (std::string player); // Remove a player from the current game
		void listPlayers (void); ///< List all players
		void startGame (void); ///< Start the game!
		void checkForWinner (void); ///< Checks for a winner, handles winning if there is one
		void nextPlayer (void); ///< Go to the next player's turn
		void rebuildBoard (void); ///< Rebuilds the entire board from scratch
		void showStats (void); ///< Display the stats of the current player
		void buyProperty (void); ///< Buy the current property
		void showProperties (void); ///< Show the properties owned by the current player

		unsigned int getPlayer (std::string name); ///< Returns the position of name in the players array, or players.size() if it fails
		void sendMessage (std::string msg); ///< Sends a message to the devopoly channel

		std::vector<std::string> splitOnSpace (std::string msg); ///< Splits a message on spaces

	protected:
		//
		/// \brief The current game state
		//
		DevopolyGameState state;

		//
		/// \brief The current message
		//
		JulieSu::Irc::Message current_message;

		//
		/// \brief The host of the current game (nick)
		//
		std::string host; 

		//
		/// \brief Our list of players in the game
		//
		std::vector<DevopolyPlayer> players;

		//
		/// \brief the current player's name (only valid in PLAY)
		//
		std::string current_player;

		//
		/// \brief The current board : do NOT adjust while a game is being played
		//
		std::vector<DevopolyBoardPiece*> board;
};

extern "C" JulieSu::Plugin* initPlugin (JulieSu::Bot* bot);
extern "C" void freePlugin (JulieSu::Plugin* plugin);

#endif // PLUGINS_DEVOPOLY_DEVOPOLY_H

