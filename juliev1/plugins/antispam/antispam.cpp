//
/// \file plugins/antispam/antispam.cpp
/// \brief AntiSpam plugin
//

#include "antispam.h"

#include <iostream>

//#define ANTISPAM_DEBUG 1

void AntiSpam::init (JulieSu::Bot* bot)
{
	this->author = "thothonegan";
	this->name = "AntiSpam";
	this->description = "Spam monitor - ignore me";

	this->type = JulieSu::PLUGIN_PRIVMSG;
	
	this->bot = bot;
}

void AntiSpam::free (void)
{}

void AntiSpam::run (JulieSu::Irc::Message message)
{
        std::string msg = message.nick + ":" + message.privmsg_msg;
	std::string target = message.privmsg_target;

	if (target == "Julie-Su" || target == "") // We are NOT handling global targets
		return;

#ifdef ANTISPAM_DEBUG
	std::cout << "[AntiSpam] " << target << " : " << msg << std::endl;
#endif

	// Ignore pull
	if (message.privmsg_msg.find ("!pull") != std::string::npos)
		return; // Ignore

	// Ignore roll
	if (message.privmsg_msg.find("!roll") != std::string::npos)
		return; // Ignore

	// Check the spammap!
	if (spammap.find (target) == spammap.end())
	{
		// Create the new entry
		std::pair<std::string, int> entry;
		entry.first = msg;
		entry.second = 1;

		spammap[target] = entry;
	}
	else
	{
		std::pair<std::string, int> entry = spammap[target];

		if (entry.first == msg) // They're repeating!
		{
			entry.second += 1;
			spammap[target] = entry;

#ifdef ANTISPAM_DEBUG
			std::cout << "[AntiSpam] They repeated " << entry.second << " times" << std::endl;
#endif
		}
		else
		{
#ifdef ANTISPAM_DEBUG
			std::cout << "[AntiSpam] Replacing [" << entry.first << "] with [" << msg << "]" << std::endl;
#endif
			// Replace
			entry.first = msg;
			entry.second = 1;
			spammap[target] = entry;
		}

		// Did they do it three times or more?
		if (entry.second >= 3)
		{
			// BAN TIME! W00T
			bot->getConnection()->send ("MODE " + target + " +b " + message.nick + "!*@*");
			bot->getConnection()->send ("KICK " + target + " " + message.nick + " [antispam!]");
	
			// Message people who care
			/// \todo Should be a config option somewhere
			std::string send_msg = "[antispam] A user has been banned via antispam ";
			send_msg += "(target:" + target +  ")" + "(nick:" + message.nick  + ")";

			// People to notify about bans
			bot->getConnection()->sendPrivMsg ("thothonegan", send_msg);
			bot->getConnection()->sendPrivMsg ("mikey", send_msg);
			bot->getConnection()->sendPrivMsg ("_Nemesis_", send_msg);
			bot->getConnection()->sendPrivMsg ("Kentaree", send_msg);
			bot->getConnection()->sendPrivMsg ("MrTus", send_msg);
			bot->getConnection()->sendPrivMsg ("Navicat", send_msg);
			bot->getConnection()->sendPrivMsg ("EddieGordo", send_msg);
			bot->getConnection()->sendPrivMsg ("EddieWork", send_msg);

			// Reset counter
			entry.second = 0;
		}
	}

	// Done
}


JulieSu::Plugin* initPlugin (JulieSu::Bot* bot)
{
	JulieSu::Plugin* temp = new AntiSpam;
	temp->init (bot);

	return temp;
}

void freePlugin (JulieSu::Plugin* plugin)
{
	plugin->free();

	delete plugin;
}

