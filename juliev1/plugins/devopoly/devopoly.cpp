//
/// \file plugins/devopoly/devopoly.cpp
/// \brief Devopoly plugin
//

#include "devopoly.h"

#include "goboardpiece.h"
#include "propertyboardpiece.h"

#include <sstream>
#include <ctime>
#include <cstdlib>

void Devopoly::init (JulieSu::Bot* bot)
{
	this->author = "thothonegan";
	this->name = "Devopoly";
	this->description = "Monopoly like clone for IRC";

	this->type = JulieSu::PLUGIN_PRIVMSG;
	
	this->bot = bot;

	// Init our stuff
	state = DEVOPOLY_STATE_NONE;

	srand(time(NULL));
}

void Devopoly::free (void)
{}

void Devopoly::run (JulieSu::Irc::Message message)
{
	current_message = message;

	// Remember that splits[0] was our command..
	std::vector<std::string> splits = splitOnSpace (message.privmsg_msg);

	// help - Displays help
	if (splits[1] == "help")
	{
		displayHelp();
		return;
	}

	// STATE_NONE - new - starts a new game with that person as the host
	else if (state == DEVOPOLY_STATE_NONE && splits[1] == "new")
	{
		newGame();
	}

	// STATE_JOIN/STATE_PLAY - end - ends a game
	else if ((state == DEVOPOLY_STATE_JOIN || state == DEVOPOLY_STATE_PLAY) && splits[1] == "end")
	{
		endGame();
	}

	// STATE_JOIN - join - joins the player that requested to the game
	else if (state == DEVOPOLY_STATE_JOIN && splits[1] == "join")
	{
		joinGame();
	}

	// STATE_JOIN/STATE_PLAY - part - parts the current game
	else if ((state == DEVOPOLY_STATE_JOIN || state == DEVOPOLY_STATE_PLAY) && splits[1] == "part")
	{
		partGame();
	}

	// STATE_JOIN/STATE_PLAY - kick - kicks the player requested from the game
	else if ((state == DEVOPOLY_STATE_JOIN || state == DEVOPOLY_STATE_PLAY) && splits[1] == "kick")
	{
		if (splits.size() == 3) // !d kick <luser>
		{
			kickPlayer(splits[2]);
		}
	}

	// STATE_JOIN - start - Starts the current game
	else if (state == DEVOPOLY_STATE_JOIN && splits[1] == "start")
	{
		startGame();
	}
	
	// STATE_JOIN/STATE_PLAY - players - lists all players in the game
	else if ((state == DEVOPOLY_STATE_JOIN || state == DEVOPOLY_STATE_PLAY)&& splits[1] == "players")
	{
		listPlayers();
	}

	// STATE_PLAY - next - go to next player if current player
	else if (state == DEVOPOLY_STATE_PLAY && splits[1] == "next")
	{
		if (current_message.nick == current_player)
			nextPlayer();
		else
			sendMessage ("It's not your turn, it's " + current_player + "'s turn!");
	}

	// STATE_PLAY - stats - shows the current stats of a player
	else if (state == DEVOPOLY_STATE_PLAY && splits[1] == "stats")
	{
		showStats();
	}

	// STATE_PLAY - buy - buy the current property if available
	else if (state == DEVOPOLY_STATE_PLAY && splits[1] == "buy")
	{
		if (current_player == current_message.nick)
			buyProperty();
		else
			sendMessage ("It's not your turn!");
	}

	// STATE_PLAY - properties - show the current properties owned by the player
	else if (state == DEVOPOLY_STATE_PLAY && splits[1] == "properties")
	{
		showProperties();
	}

	else
	{
		sendMessage("Unknown command.");
	}

	// If playing, check for a winner and that we have a valid player
	if (state == DEVOPOLY_STATE_PLAY)
	{
		checkForWinner();
	}
}

void Devopoly::displayHelp (void)
{
	switch (state)
	{
		case DEVOPOLY_STATE_NONE:
			sendMessage ("Currently no game is in progress");
			sendMessage ("new - Starts a new game with you as the host");
			break;

		case DEVOPOLY_STATE_JOIN:
			sendMessage ("Waiting for players : Host is " + host);
			sendMessage ("start - [host] Starts the current game");
			sendMessage ("end - [host] Ends the current game in progress");
			sendMessage ("kick <luser> - [host] Removes <luser> from the current game");
			sendMessage ("join - Adds you to the current game");
			sendMessage ("part - Part the current game");
			sendMessage ("players - List all players in the game");
			break;

		case DEVOPOLY_STATE_PLAY:
			sendMessage ("Playing a game : Host is " + host);
			sendMessage ("end - [host] Ends the current game in progress");
			sendMessage ("kick <luser> - [host] Removes <luser> from the current game");
			sendMessage ("part - Part the current game");
			sendMessage ("players - List all players in the game");
			sendMessage ("stats - Shows that player's current stats");
			sendMessage ("next - [current player] Done with turn (go to next player)");
			sendMessage ("buy - [current player] Buy the current property (if available)");
			break;
	}
}

void Devopoly::newGame (void)
{
	// Set the host
	host = current_message.nick;

	sendMessage ("Started a new game : " + host + " is the current host");
	state = DEVOPOLY_STATE_JOIN;

	// Auto join
	joinGame();
}

void Devopoly::endGame (void)
{
	if (host == current_message.nick)
	{
		state = DEVOPOLY_STATE_NONE;
		host = "";
		players.clear();

		sendMessage ("Ended the current game");
	}
	else
	{
		sendMessage ("You are not the host");
	}
}

void Devopoly::joinGame (void)
{
	if (getPlayer(current_message.nick) == players.size())
	{
		players.push_back (current_message.nick);
		sendMessage (current_message.nick + " has joined the game");
	}
	else
	{
		sendMessage ("You are already in the game");
	}
}

void Devopoly::partGame (void)
{
	int pos = getPlayer (current_message.nick);

	if (pos == players.size())
	{
		sendMessage ("Your not in the game!");
	}
	else
	{
		if (current_player == current_message.nick)
			nextPlayer();

		players.erase(players.begin() + pos);
		sendMessage (current_message.nick + " has parted the game");
	}
}

void Devopoly::kickPlayer (std::string player)
{
	if (current_message.nick == host)
	{
		removePlayer (player);
	}
	else
	{
		sendMessage ("You are not the host!");
	}
}

void Devopoly::removePlayer (std::string player)
{
	int pos = getPlayer (player);

	if (pos == players.size())
		sendMessage ("Player not in the game");
	else
	{
		if (current_player == player)
			nextPlayer();

		// Open all properties
		for (int x=0; x < board.size(); ++x)
		{
			if (board[x]->getType() == DEVOPOLY_BOARD_PIECE_TYPE_PROPERTY)
			{
				DevopolyPropertyBoardPiece* prop = (DevopolyPropertyBoardPiece*) board[x]; 
				if (prop->getOwner() == player)
					prop->setOwner ("");
			}
		}

		players.erase (players.begin() + pos);
		sendMessage (player + " has been removed from the game");
	}

}

void Devopoly::listPlayers (void)
{
	std::stringstream str;
	str << "Current players : ";

	for (int x=0; x < players.size(); ++x)
	{
		str << players[x].getName() << " ";
	}

	sendMessage (str.str());
}

void Devopoly::buyProperty (void)
{
	int cur_id = getPlayer (current_player);

	int cur_pos = players[cur_id].getPosition();

	if (board[cur_pos]->getType() == DEVOPOLY_BOARD_PIECE_TYPE_PROPERTY)
	{
		DevopolyPropertyBoardPiece* piece = (DevopolyPropertyBoardPiece*) board[cur_pos];

		// Is it owned already?
		if (piece->getOwner() != "")
		{
			sendMessage ("Owned by someone already");
		}
		else
		{
			if (players[cur_id].getMoney() >= piece->getPrice())
			{
				// Buy it
				std::stringstream q; q << "Bought " << piece->getName() << " for " << piece->getPrice() << " bits";
				sendMessage (q.str());

				players[cur_id].setMoney (players[cur_id].getMoney() - piece->getPrice());
				piece->setOwner (current_player);
			}
			else
			{
				sendMessage ("You dont have enough money");
			}
		}
	}
	else
	{
		sendMessage ("This isnt a property!");
	}
}

void Devopoly::showProperties (void)
{
	std::stringstream str;

	str << "[" << current_message.nick << "] Properties owned : ";
	for (int x=0; x < board.size(); ++x)
	{
		if (board[x]->getType() == DEVOPOLY_BOARD_PIECE_TYPE_PROPERTY)
		{
			DevopolyPropertyBoardPiece* piece = (DevopolyPropertyBoardPiece*) board[x];

			if (piece->getOwner() == current_message.nick)
			{
				str << piece->getName() << " ";
			}
		}
	}

	sendMessage (str.str());
}

unsigned int Devopoly::getPlayer (std::string name)
{
	for (int x=0; x < players.size(); ++x)
	{
		if (players[x].getName() == name)
			return x;
	}

	return players.size();
}

void Devopoly::startGame (void)
{
	if (current_message.nick == host)
	{
		// Start the game!
		state = DEVOPOLY_STATE_PLAY;

		// Rebuild the board
		rebuildBoard();

		// Randomize the players list
		std::random_shuffle (players.begin(), players.end());

		std::stringstream players_str;
		for (int x=0; x < players.size(); ++x)
		{
			players_str << players[x].getName() << " ";
			players[x].setMoney (1500);
			players[x].setPosition (0); // Start at the beginning
		}

		sendMessage ("Started a new game : order is " + players_str.str());
		sendMessage ("Everyone starts with 1500 bits");

		current_player = "";
		nextPlayer();
	}
	else
	{
		sendMessage ("Only the host can start the game");
	}
}

void Devopoly::checkForWinner (void)
{
	if (players.size() == 1)
	{
		// Winner!
		sendMessage ("The winner is " + players[0].getName());

		current_message.nick = host; // Cheat
		endGame();
	}
}

void Devopoly::nextPlayer (void)
{
	int x = getPlayer (current_player);
	x++;

	if (x >= players.size())
		x = 0;

	current_player = players[x].getName();
	sendMessage ("It is now " + current_player + "'s turn");

	// Move them
	int val1 = (rand() % 5) + 1;
	int val2 = (rand() % 5) + 1;

	int spaces = val1 + val2;

	if (val1 == val2)
		spaces *= 2; // Doubles!

	std::stringstream s; 
	s << "Rolled " << val1 << " and " << val2 << " so " << spaces << ". Moving...";
	sendMessage (s.str());

	while (spaces > 0)
	{
		if (players[x].getPosition() + spaces >= board.size())
		{
			// Wrap around
			players[x].setMoney (players[x].getMoney() + 200);
			sendMessage ("You went all the way around the board! 200 bits for you!");
			spaces -= (board.size() - players[x].getPosition());
			players[x].setPosition (0);
		}
		else
		{
			players[x].setPosition (players[x].getPosition() + spaces);
			spaces = 0;
		}
	}

	// Output the new position
	sendMessage ("You are now at " + board[players[x].getPosition()]->getName());

	// Perform its action
	board[players[x].getPosition()]->perform (&players[x], &players);
}

void Devopoly::rebuildBoard (void)
{
	// Rebuilds the entire board from scratch
	for (int x=0; x < board.size(); ++x)
		delete board[x];

	board.clear();

	board.push_back (new DevopolyGoBoardPiece("Dole Office", this));
	board.push_back (new DevopolyPropertyBoardPiece("Fiddling Drunkard", this, DEVOPOLY_PROPERTY_TYPE_PURPLE));
	// COMMUNITY CHEST
	board.push_back (new DevopolyPropertyBoardPiece("Vee City", this, DEVOPOLY_PROPERTY_TYPE_PURPLE));
	// INCOME TAX
	// READING RAILROAD
	board.push_back (new DevopolyPropertyBoardPiece("Linux", this, DEVOPOLY_PROPERTY_TYPE_CYAN));
	// CHANCE
	board.push_back (new DevopolyPropertyBoardPiece("MacOSX", this, DEVOPOLY_PROPERTY_TYPE_CYAN));
	board.push_back (new DevopolyPropertyBoardPiece("Windows", this, DEVOPOLY_PROPERTY_TYPE_CYAN));
	// JUST VISITING
	board.push_back (new DevopolyPropertyBoardPiece("Slashdot", this, DEVOPOLY_PROPERTY_TYPE_BROWN));
	// ELECTRIC COMPANY
	board.push_back (new DevopolyPropertyBoardPiece("Bash.org", this, DEVOPOLY_PROPERTY_TYPE_BROWN));
	board.push_back (new DevopolyPropertyBoardPiece("4chan", this, DEVOPOLY_PROPERTY_TYPE_BROWN));
	// PENN RAILROAD
	board.push_back (new DevopolyPropertyBoardPiece("ZKAT8IT", this, DEVOPOLY_PROPERTY_TYPE_ORANGE));
	// COMMUNITY CHEST
	board.push_back (new DevopolyPropertyBoardPiece("Moggie100", this, DEVOPOLY_PROPERTY_TYPE_ORANGE));
	board.push_back (new DevopolyPropertyBoardPiece("TKF15H", this, DEVOPOLY_PROPERTY_TYPE_ORANGE));
	// FREE PARKING
	board.push_back (new DevopolyPropertyBoardPiece("IdleBot", this, DEVOPOLY_PROPERTY_TYPE_RED));
	// CHANCE
	board.push_back (new DevopolyPropertyBoardPiece("Devbot", this, DEVOPOLY_PROPERTY_TYPE_RED));
	board.push_back (new DevopolyPropertyBoardPiece("Julie-Su", this, DEVOPOLY_PROPERTY_TYPE_RED));
	// BO RAILROAD
	board.push_back (new DevopolyPropertyBoardPiece("Peer", this, DEVOPOLY_PROPERTY_TYPE_YELLOW));
	board.push_back (new DevopolyPropertyBoardPiece("Ping", this, DEVOPOLY_PROPERTY_TYPE_YELLOW));
	// WATER WORKS
	board.push_back (new DevopolyPropertyBoardPiece("Broken Pipe", this, DEVOPOLY_PROPERTY_TYPE_YELLOW));
	// GO TO JAIL
	board.push_back (new DevopolyPropertyBoardPiece("absinthe.devhat.net", this, DEVOPOLY_PROPERTY_TYPE_GREEN));
	board.push_back (new DevopolyPropertyBoardPiece("dortmunder.devhat.net", this, DEVOPOLY_PROPERTY_TYPE_GREEN));
	// COMMUNITY CHEST
	board.push_back (new DevopolyPropertyBoardPiece("cobra.devhat.net", this, DEVOPOLY_PROPERTY_TYPE_GREEN));
	// SHORT LINE
	// CHANCE
	board.push_back (new DevopolyPropertyBoardPiece("#lobby", this, DEVOPOLY_PROPERTY_TYPE_BLUE));
	// LUXERY TAX
	board.push_back (new DevopolyPropertyBoardPiece("#opers", this, DEVOPOLY_PROPERTY_TYPE_BLUE));
}

void Devopoly::showStats (void)
{
	std::stringstream s;

	int player = getPlayer(current_message.nick);

	if (player == players.size())
	{
		sendMessage ("Your not playing!");
	}
	else
	{
		s << "[" << current_message.nick << "] " << players[player].getMoney() << " bits. Currently on : " << board[players[player].getPosition()]->getName();
	}
	sendMessage (s.str());
}

void Devopoly::sendMessage (std::string msg)
{
		bot->getConnection()->sendPrivMsg (current_message.privmsg_target, "[devopoly] " + msg);
}

std::vector<std::string> Devopoly::splitOnSpace (std::string msg)
{
	std::vector<std::string> splits;

	int cur_pos = 0;
	int last_split = 0;

	while (cur_pos != msg.length())
	{
		if (msg[cur_pos] == ' ')
		{
			// Split here!
			std::string split_str = msg.substr (last_split, cur_pos - last_split); // Dont include space
			splits.push_back (split_str);

			// Update our position
			last_split = cur_pos + 1;
		}

		// Next pos
		cur_pos++;
	}

	// Last split
	splits.push_back (msg.substr(last_split));

	return splits;
}

JulieSu::Plugin* initPlugin (JulieSu::Bot* bot)
{
	JulieSu::Plugin* temp = new Devopoly;
	temp->init (bot);

	return temp;
}

void freePlugin (JulieSu::Plugin* plugin)
{
	plugin->free();

	delete plugin;
}

