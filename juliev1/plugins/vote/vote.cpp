//
/// \file plugins/vote/vote.cpp
/// \brief Vote plugin
//

#include "vote.h"

#include <cstring>
#include <sstream>
#include <iostream>
#include <algorithm>

void Vote::init (JulieSu::Bot* bot)
{
	this->author = "thothonegan";
	this->name = "Vote";
	this->description = "Vote for stupid stuff!";

	this->type = JulieSu::PLUGIN_PRIVMSG;
	
	this->bot = bot;

	is_voting = false;
}

void Vote::free (void)
{}

void Vote::run (JulieSu::Irc::Message message)
{
	// Respond to their message
	std::string arguments = message.privmsg_msg;
	arguments = arguments.substr(arguments.find(" ")+1);

	// Help on voting
	if (arguments.substr (0, strlen("help")) == "help")
	{
		std::stringstream str;

		str << "[vote] !vote new <question> : <choice1> <choice2> | !vote <choice> | !vote status | !vote help | !vote end";

		if (message.privmsg_target == bot->getName())
			bot->getConnection()->sendPrivMsg (message.nick, str.str());
		else
			bot->getConnection()->sendPrivMsg (message.privmsg_target, str.str());
	}

	// New vote
	else if (arguments.substr (0, strlen("new")) == "new")
	{
		std::stringstream str;

		if (!is_voting)
		{
			if (arguments.find(" ") == std::string::npos)
				return;

			arguments = arguments.substr (arguments.find(" ")+1);

			if (arguments.find(" : ") == std::string::npos)
				return;

			std::string voting = arguments.substr (0, arguments.find (" : "));

			issue = voting;

			std::string options = arguments.substr (arguments.find (" : ") + 3);
			choices.clear();
			people_voted.clear();

			vote_creator = message.nick;
			vote_creator_host = message.username + "@" + message.host;

			while (options.find  (" ") != std::string::npos)
			{
				std::string ch = options.substr (0, options.find(" "));

				choices[ch] = 0;
				options = options.substr (options.find (" ")+1);
			}

			// rest
			choices[options] = 0;

			// Output
			str << "[vote] New vote for '" << issue << "' with choices";
			std::map<std::string, int>::iterator iter;
			for (iter = choices.begin(); iter != choices.end(); ++iter)
			{
				str << " '" << iter->first << "'";
			}

			is_voting = true;
		}
		else
		{
			str << "[vote] Already in progress : '" << issue << "' with choices";
			std::map<std::string, int>::iterator iter;
			for (iter = choices.begin(); iter != choices.end(); ++iter)
			{
				str << " '" << iter->first << "'";
			}
		}

		if (message.privmsg_target == bot->getName())
			bot->getConnection()->sendPrivMsg (message.nick, str.str());
		else
			bot->getConnection()->sendPrivMsg (message.privmsg_target, str.str());
	}

	// End voting
	else if (arguments.substr (0, strlen("end")) == "end")
	{
		
		std::stringstream str;
		if (is_voting)
		{
			if (message.username + "@" + message.host != vote_creator_host && bot->getLevel (message.userhost) != JulieSu::LEVEL_ADMIN)
			{
				str << "[vote] You are not the vote creator!";
			}
			else
			{
				str << "[vote] Finished vote '" << issue << "' with results";
				std::map<std::string, int>::iterator iter;
				for (iter = choices.begin(); iter != choices.end(); ++iter)
				{
					str << " '" << iter->first << "':" << iter->second;
				}

				is_voting = false;
			}
		}
		else
		{
			str << "[vote] No vote in progress";
		}

		if (message.privmsg_target == bot->getName())
			bot->getConnection()->sendPrivMsg (message.nick, str.str());
		else
			bot->getConnection()->sendPrivMsg (message.privmsg_target, str.str());
	}

	else if (arguments.substr (0, strlen("status")) == "status")
	{
		std::stringstream str;
		if (is_voting)
		{
			str << "[vote] Vote by " << vote_creator <<  " : '" << issue << "' with choices";
			std::map<std::string, int>::iterator iter;
			for (iter = choices.begin(); iter != choices.end(); ++iter)
			{
				str << " '" << iter->first << "':" << iter->second;
			}
		}
		else
		{
			str << "[vote] No vote in progress";
		}

		if (message.privmsg_target == bot->getName())
			bot->getConnection()->sendPrivMsg (message.nick, str.str());
		else
			bot->getConnection()->sendPrivMsg (message.privmsg_target, str.str());
	}

	// Else a vote
	else
	{
		std::stringstream str;
		if (is_voting)
		{
			if (std::find(people_voted.begin(), people_voted.end(), message.username + "@" + message.host) == people_voted.end())
			{
				std::string vote = arguments;

				if (choices.find (vote) != choices.end())
				{
					choices[vote] += 1;
					people_voted.push_back (message.username + "@" + message.host);
					str << "[vote] Vote for '" << vote << "' counted.";
				}
				else
				{
					str << "[vote] Invalid choice (see !vote status)";
				}
			}
			else
			{
				str << "[vote] You have already voted!";
			}
		}
		else
		{
			str << "[vote] No vote in progress";
		}

		if (message.privmsg_target == bot->getName())
			bot->getConnection()->sendPrivMsg (message.nick, str.str());
		else
			bot->getConnection()->sendPrivMsg (message.privmsg_target, str.str());
	}

}


JulieSu::Plugin* initPlugin (JulieSu::Bot* bot)
{
	JulieSu::Plugin* temp = new Vote;
	temp->init (bot);

	return temp;
}

void freePlugin (JulieSu::Plugin* plugin)
{
	plugin->free();

	delete plugin;
}

