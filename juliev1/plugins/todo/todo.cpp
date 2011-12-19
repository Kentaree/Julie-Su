//
/// \file plugins/todo/todo.cpp
/// \brief Todo plugin
//

#include "todo.h"

#include <cstdlib>
#include <sstream>
#include <cstring>

#include <fstream>
#include <iostream>

void Todo::init (JulieSu::Bot* bot)
{
	this->author = "thothonegan";
	this->name = "Todo";
	this->description = "Manages todo lists for users";

	this->type = JulieSu::PLUGIN_PRIVMSG;
	
	this->bot = bot;

	// Read the given file (currently hardcoded)
	readTodoList ("todo.txt");
}

void Todo::free (void)
{}

void Todo::run (JulieSu::Irc::Message message)
{
	// Respond to their message
	std::string arguments = message.privmsg_msg;
	arguments = arguments.substr(arguments.find(" ")+1);

	// Are they requesting a list?
	if (arguments.substr (0, strlen("list")) == "list")
	{
		// Yep : anyone specific?
		if (arguments == "list") // Nope
		{
			// Display their list
			if (message.privmsg_target == bot->getName())
				outputUserList (message.nick, message.nick, true);
			else
				outputUserList (message.nick, message.privmsg_target, false);
		}
		else
		{
			arguments = arguments.substr (arguments.find(" ")+1); // Whos list we want

			std::string user = arguments;

			if (message.privmsg_target == bot->getName())
				outputUserList (user, message.nick, true);
			else
				outputUserList (user, message.privmsg_target, false);
		}

		return; // Done
	}

	// add
	else if (arguments.substr (0, strlen("add")) == "add")
	{
        	if (strlen("add") + 1 >= arguments.size())
           		return; // stupid idiot

        	arguments = arguments.substr (strlen("add") + 1);

		// Add to their todo list
		addToUserList (message.nick, arguments);

		std::stringstream msg; msg << "[todo] [" << message.nick << "] Added";

		if (message.privmsg_target == bot->getName())
			bot->getConnection()->sendPrivMsg (message.nick, msg.str());
		else
			bot->getConnection()->sendPrivMsg (message.privmsg_target, msg.str());
	}

	// remove
	else if (arguments.substr (0, strlen("remove")) == "remove")
	{
        	if (strlen("remove") + 1 >= arguments.size())
            		return; // stupid idiot

        	arguments = arguments.substr (strlen("remove") + 1);

		// Convert to number
		int num = atoi(arguments.c_str());

		removeFromUserList (message.nick, num);

		std::stringstream msg; msg << "[todo] [" << message.nick << "] Message " << num << " deleted.";

		if (message.privmsg_target == bot->getName())
			bot->getConnection()->sendPrivMsg (message.nick, msg.str());
		else
			bot->getConnection()->sendPrivMsg (message.privmsg_target, msg.str());

	}

	// Swap
	else if (arguments.substr (0, strlen("swap")) == "swap")
	{

		if (strlen("swap") + 1 >= arguments.size())
			return; // Stupid idiot

		arguments = arguments.substr (strlen("swap") + 1);

		// Two numbers are our input
		std::string snum_1 = arguments.substr (0, arguments.find(" "));
		std::string snum_2 = arguments.substr (arguments.find(" ")+1);

		// Convert
		int item1 = atoi(snum_1.c_str());
		int item2 = atoi(snum_2.c_str());

		std::stringstream msg;

		msg << Todo::swapUserListElements (message.nick, item1, item2);

		if (message.privmsg_target == bot->getName())
			bot->getConnection()->sendPrivMsg (message.nick, msg.str());
		else
			bot->getConnection()->sendPrivMsg (message.privmsg_target, msg.str());
	}

	// Help
	else if (arguments.substr (0, strlen("help")) == "help")
	{
		std::stringstream msg;

		msg << "[todo] ";
		msg << "!todo add <message> : Adds a message to your list | ";
		msg << "!todo list [person] : Shows [person]'s list, or your own | ";
		msg << "!todo remove <number> : Removes item <number> from your list | ";
		msg << "!todo swap <num1> <num2> : Swaps items <num1> and <num2> in your list";

		if (message.privmsg_target == bot->getName())
			bot->getConnection()->sendPrivMsg (message.nick, msg.str());
		else
			bot->getConnection()->sendPrivMsg (message.privmsg_target, msg.str());
	}

}

void Todo::outputUserList (std::string nick, std::string target, bool pm)
{
	// Find nick's list
	for (int x=0; x < todolists.size(); ++x)
	{
		if (todolists[x].first == nick)
		{
			// This is the list!
			std::vector<std::string> list = todolists[x].second;

			std::stringstream str;

			for (int y=0; y < list.size(); ++y)
			{
				if (!pm)
				{
					str << " [" << y << "] " << list[y];
				}
				else
				{
					// Just output
					str.str(""); str.clear();
					str << "[todo] [" << y << "] " << list[y];
					bot->getConnection()->sendPrivMsg (target, str.str());
				}
			}

			// Done
			if (!pm)
			{
				bot->getConnection()->sendPrivMsg (target, std::string("[todo] ") + "[" + nick + "]" + str.str());
			}
			return;
		}
	}

	// Not found
	bot->getConnection()->sendPrivMsg (target, std::string("[todo] ") + "[" + nick + "] No list");
	return;
}

void Todo::addToUserList (std::string nick, std::string message)
{
	// Find the list
	for (int x=0; x < todolists.size(); ++x)
	{
		if (todolists[x].first == nick)
		{
			// Add it
			todolists[x].second.push_back (message);

			// Rewrite our todo file
			writeTodoList ("todo.txt");

			return;
		}
	}

	// Not found : create a list
	std::pair<std::string, std::vector<std::string> > pair;
	pair.first = nick;
	todolists.push_back (pair);

	addToUserList (nick, message); // Try again
}

void Todo::removeFromUserList (std::string nick, int num)
{
	// Find the list
	for (int x=0; x < todolists.size(); ++x)
	{
		if (todolists[x].first == nick)
		{
			if (num >= todolists[x].second.size())
				return;
			else
				todolists[x].second.erase (todolists[x].second.begin() + num);

			writeTodoList ("todo.txt");

			return;
		}
	}

	// Didnt find it
	return;
}

void Todo::writeTodoList (std::string filename)
{
	// Open the file
	std::ofstream file;

	file.open (filename.c_str());

	// Format is username\ntodo item\ntodo item\n\nusername\ntodo item\ntodo item etc
	// Newlines seperate new sections
	for (int x=0; x < todolists.size(); ++x)
	{
		// Current list
		std::string& username = todolists[x].first;
		std::vector<std::string>& curlist = todolists[x].second;

		// Write the name
		file << username << std::endl;

		// Write the list
		for (int y=0; y < curlist.size(); ++y)
		{
			file << curlist[y]<< std::endl;
		}

		// Done : empty line
		file << std::endl;
	}

	// Done writing
	file.close();

}

void Todo::readTodoList (std::string filename)
{
	// Open the file
	std::ifstream file;

	file.open (filename.c_str());

	if (file.fail())
		return; // Nothing to do : no file

	while (!file.eof())
	{
		// Get the current username
		std::string cur_username;
		getline (file, cur_username);
		std::vector<std::string> todos;

		if (cur_username != "")
		{
			// Now read todos till end of section
			std::string cur_line="asdf";
			while (cur_line != "")
			{
				getline (file, cur_line);
	
				if (cur_line != "")
				{
					// Add it
					todos.push_back (cur_line);
				}
			}

			// Done: add this person
			todolists.push_back (std::make_pair(cur_username, todos));
		}

	}

	// Done
	file.close();
}

std::string Todo::swapUserListElements (std::string nick, int item1, int item2)
{
	std::stringstream msg;

	// Find the list
	for (int x=0; x < todolists.size(); ++x)
	{
		if (todolists[x].first == nick)
		{
			// Found it!

			if (item1 >= todolists[x].second.size() || item2 >= todolists[x].second.size())
			{
				msg << "[todo] [" << nick << "] One of the items doesnt exist!";
				return msg.str();
			}
			else
			{
				// Swap them
				std::vector<std::string>& cur_list = todolists[x].second;

				std::swap (cur_list[item1], cur_list[item2]);
				msg << "[todo] [" << nick << "] Items " << item1 << " and " << item2 << " swapped.";
				return msg.str();
			}
		}
	}

	// Not found
	msg << "[todo] [" << nick << "] No list!";

	return msg.str();
}


JulieSu::Plugin* initPlugin (JulieSu::Bot* bot)
{
	JulieSu::Plugin* temp = new Todo;
	temp->init (bot);

	return temp;
}

void freePlugin (JulieSu::Plugin* plugin)
{
	plugin->free();

	delete plugin;
}

