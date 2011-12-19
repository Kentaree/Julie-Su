//
/// \file bot/bot.cpp
/// \brief A bot
//

#include "bot.h"
#include "plugin.h"

#include <ctime>
#include <sstream>

#include "output.h"

namespace JulieSu
{
	Bot::Bot (std::string name, std::string password) : connection (NULL), manager (this)
	{
		this->name = name;
		this->password = password;
		this->last_message_time = time(NULL);

		// Set the start time
		start_time = time(NULL);
	}

	Bot::~Bot (void)
	{
		if (connection)
			delete connection;
	}

	void Bot::setServer (std::string hostname, int port)
	{
		this->server_hostname = hostname;
		this->server_port = port;
	}

	void Bot::connect (void)
	{
		this->connection = new JulieSu::Irc::Connection (server_hostname, name, password);
		has_authed = false;

		// Join channels at initLogin
	}

	void Bot::reconnect (void)
	{
		delete this->connection;
		connect();
	}

	void Bot::processMessages (void)
	{
		std::string message = connection->receive();

		static time_t start_time = time (NULL);

		// If 5 seconds have passed, auth
		if (!has_authed)
		{
			time_t cur_time = time (NULL);
			if (cur_time >  start_time + 5)
			{
				// Auth!
				connection->initLogin();

				// Join all our channels
				for (int x=0; x < channels.size(); ++x)
				{
					connection->joinChannel (channels[x]);
				}

				has_authed = true;
			}
		}

		while (message != "")
		{
			// Split the message based on \n
			std::vector<std::string> msgs;

			while (message.find("\n") != std::string::npos)
			{
				// Split on this
				msgs.push_back (message.substr (0, message.find("\n")));
				message = message.substr(message.find("\n")+1);

				// Remove \r
				while (msgs[msgs.size()-1].find("\r") != std::string::npos)
					msgs[msgs.size()-1] = msgs[msgs.size()-1].erase(msgs[msgs.size()-1].find("\r"));
			}

			// Grab the last component if there is one
			if (message != "")
				msgs.push_back (message);

			// Now parse all messages
			while (msgs.size() > 0)
			{
				message = msgs[0];
				msgs.erase(msgs.begin());


				last_message_time = time(NULL);

				std::stringstream str;
				str << "[" << name << "]" << message;
				Output::write (str.str());

				// Process raw
				for (std::map<std::string, std::string>::iterator iter = raw_plugins.begin(); iter != raw_plugins.end(); ++iter)
				{
					Irc::Message msg = connection->parse(message);
					if (msg.command == iter->first)
					{
						// Match!
						manager.runPlugin ((*iter).second, msg);
					}
				}

				Irc::Message msg = connection->parse(message);

				if (getLevel (msg.userhost) == JulieSu::LEVEL_IGNORE)
				{
					Output::write ("Ignoring message");
					message = connection->receive();
					continue; // Nobody cares about this user
				}

				// Process ctcp
				if (msg.privmsg_msg[0] == '\001') // CTCP message
				{
					Output::write ("CTCP message!");

					for (std::map<std::string, std::string>::iterator iter = ctcp_plugins.begin(); iter != ctcp_plugins.end(); ++iter)
					{
						if (msg.privmsg_msg.substr(1, (*iter).first.size()) == (*iter).first)
						{
							// Match!
							manager.runPlugin ((*iter).second, msg);
						}
					}
				}


				// Process privmsg
				for (std::map<std::string, std::string>::iterator iter = global_privmsg_plugins.begin(); iter != global_privmsg_plugins.end(); ++iter)
				{
					if ((msg.privmsg_msg.substr(0, (*iter).first.size() + 1) == (*iter).first + " ") || msg.privmsg_msg == (*iter).first || (*iter).first == "")
					{
						manager.runPlugin ((*iter).second, msg);
					}
				}

				// Process privmsg (channel)
				for (std::map<std::pair<std::string, std::string>, std::string >::iterator iter = channel_privmsg_plugins.begin(); iter != channel_privmsg_plugins.end(); ++iter)
				{
					if (((msg.privmsg_msg.substr(0, (*iter).first.first.size() + 1) == (*iter).first.first + " ") || (msg.privmsg_msg == (*iter).first.first) ) && msg.privmsg_target == (*iter).first.second)
					{
						manager.runPlugin ((*iter).second, msg);
					}
				}
			}
			message = connection->receive();
		}

		// Check if time has expired
		if (time(NULL) - last_message_time > 300)
		{
			std::stringstream str;
			str << "[" << name << "]" << "Reconnecting due to inactivity";
			Output::write (str.str());

			last_message_time = time(NULL);
			reconnect();
		}

		// Tell all plugins that we looped
		manager.loopPlugins();
	}

	void Bot::addChannel (std::string name)
	{
		this->channels.push_back (name);

		if (connection)
			connection->joinChannel (name);
	}

	void Bot::linkPlugin (std::string plugin, std::string key)
	{
		int type = manager.getPlugin(plugin)->getType();

		std::stringstream str;
		str << "[" << name << "]" << "Linking plugin";
		Output::write (str.str());

		if (type == JulieSu::PLUGIN_RAW)
		{
			std::stringstream msg;
			msg << "[" << name << "]" << "Linked raw plugin to : '" << key << "'";
			Output::write (msg.str());

			raw_plugins.insert(std::make_pair(key, plugin));
		}
		else if (type == JulieSu::PLUGIN_CTCP)
		{
			std::stringstream msg;
			msg << "[" << name << "]" << "Linked ctcp plugin to : '" << key << "'";
			Output::write (msg.str());

			ctcp_plugins.insert(std::make_pair(key, plugin));
		}

		else if (type == JulieSu::PLUGIN_PRIVMSG)
		{
			std::stringstream msg;
			msg << "[" << name << "]" << "Linked global privmsg plugin to : '" << key << "'" << std::endl;
			Output::write (msg.str());

			global_privmsg_plugins.insert(std::make_pair(key, plugin));
		}

	}

	void Bot::linkPlugin (std::string plugin, std::string key, std::string channel)
	{
		int type = manager.getPlugin(plugin)->getType();

		std::stringstream msg;
		msg << "[" << name << "]" << "Linking plugin" << std::endl;
		Output::write (msg.str());

		if (type == JulieSu::PLUGIN_PRIVMSG)
		{
			std::stringstream str;
			str << "[" << name << "]" << "Linked privmsg plugin to : '" << key << "' for channel : '" << channel << "'" << std::endl;
			Output::write (str.str());

			std::pair<std::string, std::string> pair; pair.first = key; pair.second = channel;
			channel_privmsg_plugins.insert(std::make_pair(pair, plugin));
		}


	}

	JulieSu::Irc::Connection* Bot::getConnection (void)
	{
		return connection;
	}

	void Bot::loadPlugin (std::string name, std::string location)
	{
		manager.loadPlugin(name, location);
	}

	std::string Bot::getName (void)
	{
		return name;
	}

	void Bot::setLevel (std::string mask, JulieSu::Level level)
	{
		std::pair <std::string, JulieSu::Level> pair;
		pair.first = mask;
		pair.second = level;

		user_levels.push_front (pair);
	}

	JulieSu::Level Bot::getLevel (std::string string)
	{
		for (std::list<std::pair<std::string, JulieSu::Level> >::iterator iter = user_levels.begin();
			iter != user_levels.end(); ++iter)
		{
			// Get the mask
			std::string mask = iter->first;

			// See if it matches
			int pos_in_mask = 0;
			int pos_in_string = 0;
			bool matched = true;

			while (pos_in_mask < mask.size())
			{
				// Two possibilities

				// One : we're at a *
				if (mask[pos_in_mask] == '*')
				{
					if (pos_in_mask + 1 == mask.size())
					{
						// Out of mask : finished successfully
						matched = true;
						break;
					}

					// Get the next mask character
					while (mask[pos_in_mask] == '*')
						pos_in_mask++;

					// This is what we're matching
					while (string[pos_in_string] != mask[pos_in_mask])
					{
						// Next character
						pos_in_string++;

						if (pos_in_string >= string.size())
						{
							// Ran out of string : failed
							matched = false;
							break;
						}
					}
				}
				else // Regular character
				{
					if (mask[pos_in_mask] != string[pos_in_string])
					{
						// Fail
						matched = false;
						break;
					}
					else
					{
						// Match : next character
						pos_in_mask++;
						pos_in_string++;
					}
				}
			}

			if (matched)
				return iter->second;
		}

		// Ignore anyone we dont know
		return JulieSu::LEVEL_IGNORE;
	}

	void Bot::removeLevel (std::string string)
	{
		for (std::list<std::pair<std::string, JulieSu::Level> >::iterator iter = user_levels.begin();
			iter != user_levels.end(); iter++)
		{
			if (iter->first == string)
			{
				// Remove
				user_levels.erase (iter);
				return;
			}
		}
	}

	std::list <std::pair <std::string, JulieSu::Level> > Bot::getLevels (void)
	{
		return user_levels;
	}

	std::string Bot::getUptime (void)
	{
		time_t cur_time = time(NULL);

		time_t diff = cur_time - start_time;

		#define SECS_IN_DAY (60*60*24)
		#define SECS_IN_HOUR (60*60)
		#define SECS_IN_MIN (60)

		unsigned int days = diff / SECS_IN_DAY;
		diff -= days * SECS_IN_DAY;


		unsigned int hours = diff / SECS_IN_HOUR;
		diff -= hours * SECS_IN_HOUR;

		unsigned int minutes = diff / SECS_IN_MIN;
		diff -= minutes * SECS_IN_MIN;

		unsigned int seconds = diff;

		std::stringstream s;
		s << days << " days " << hours << ":" << minutes << ":" << seconds;

		return s.str();
	}


	std::multimap<std::string, std::string> Bot::getRawPlugins (void)
	{
		return raw_plugins;
	}

	std::multimap<std::string, std::string> Bot::getCtcpPlugins (void)
	{
		return ctcp_plugins;
	}

	std::multimap<std::string, std::string> Bot::getGlobalPrivmsgPlugins (void)
	{
		return global_privmsg_plugins;
	}

	std::multimap<std::pair<std::string, std::string>, std::string > Bot::getChannelPrivmsgPlugins (void)
	{
		return channel_privmsg_plugins;
	}

	JulieSu::PluginManager* Bot::getPluginManager (void)
	{
		return &manager;
	}

	std::vector<std::string> Bot::getChannels (void)
	{
		return channels;
	}
}

