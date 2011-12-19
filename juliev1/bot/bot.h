//
/// \file bot/bot.h
/// \brief Bot class
//

#ifndef BOT_BOT_H
#define BOT_BOT_H

#include <string>
#include <map>
#include <utility>
#include <ctime>
#include <list>

#include "connection.h"
#include "level.h"
#include "pluginmanager.h"

namespace JulieSu
{
	//
	/// \brief A bot controlled by JS
	//
	class Bot
	{
		public:
			//
			/// \brief Constructor
			/// \param name The name of the bot
			/// \param password The nickserv password of the bot
			//
			Bot (std::string name, std::string password);

			//
			/// \brief Destructor
			//
			virtual ~Bot (void);

			//
			/// \brief Sets a server for the bot
			/// \param hostname The hostname of the server
			/// \param port The port the irc server is running on
			//
			void setServer (std::string hostname, int port);

			//
			/// \brief Connects to the server : Also joins all channels added
			/// \note Call after set server
			//
			void connect (void);

			//
			/// \brief Reconnect to the server
			//
			void reconnect (void);

			//
			/// \brief Process all messages in the queue
			/// \return true if we got a message
			//
			void processMessages (void);

			//
			/// \brief Adds a channel to the list. Will also join if connected, otherwise joins on connect()
			//
			void addChannel (std::string channel);

			//
			/// \brief Links a plugin to a key
			/// \param plugin The plugin to link
			/// \param key The key to link the plugin to
			//
			void linkPlugin (std::string plugin, std::string key);

			//
			/// \brief Links a plugin to a key and a channel
			/// \param plugin The plugin to link
			/// \param key The key to link the plugin to
			/// \param channel The channel this is linked to
			//
			void linkPlugin (std::string plugin, std::string key, std::string channel);

			//
			/// \brief Get the internal connection
			//
			JulieSu::Irc::Connection* getConnection (void);

			//
			/// \brief Load a plugin
			/// \param name The name of the plugin to load
			/// \param location The location of the plugin
			//
			void loadPlugin (std::string name, std::string location);

			//
			/// \brief Get the name of the bot
			/// \return The name of the bot
			//
			std::string getName (void);

			//
			/// \brief Set the admin level of a given mask
			/// \param mask Mask to set the level as
			/// \param level The level to set the mask to
			//
			void setLevel (std::string mask, JulieSu::Level level);

			//
			/// \brief Returns the priority of a given string
			/// \param string The string we need to test masks against
			//
			Level getLevel (std::string string);

			//
			/// \brief Remove a level from our mask set
			//
			void removeLevel (std::string mask);

			//
			/// \brief Returns the list of levels
			//
			std::list<std::pair<std::string, JulieSu::Level> > getLevels (void);

			//
			/// \brief Get the bot's uptime as a string
			//
			std::string getUptime (void);

			//
			/// \brief Get the list of raw plugins
			//
			std::multimap<std::string, std::string> getRawPlugins (void);

			//
			/// \brief Get the list of ctcp plugins
			//
			std::multimap<std::string, std::string> getCtcpPlugins (void);

			//
			/// \brief Get the list of global privmsg plugins
			//
			std::multimap<std::string, std::string> getGlobalPrivmsgPlugins (void);

			//
			/// \brief Get the list of channel privmsg plugins
			//
			std::multimap<std::pair<std::string, std::string>, std::string > getChannelPrivmsgPlugins (void);

			//
			/// \brief Get the current plugin manager
			//
			JulieSu::PluginManager* getPluginManager (void);

			//
			/// \brief Channels JS is a part of
			/// \return our list of channels
			//
			std::vector<std::string> getChannels (void);

		protected:
			//
			/// \brief Name of the bot
			//
			std::string name;

			//
			/// \brief NickServ password for the bot
			//
			std::string password;

			//
			/// \brief The server name
			//
			std::string server_hostname;

			//
			/// \brief The server port
			//
			int server_port;

			//
			/// \brief The server connection
			//
			JulieSu::Irc::Connection* connection;

			//
			/// \brief The channels this bot is on
			//
			std::vector<std::string> channels;

			//
			/// \brief The bot's plugin manager : Every bot can have different plugins loaded
			//
			JulieSu::PluginManager manager;

			// PLUGIN lists
			// We have one list for every type
			
			//
			/// \brief Raw plugins
			/// \note format : key, plugin
			//
			std::multimap<std::string, std::string> raw_plugins;

			//
			/// \brief Ctcp plugins
			/// \note Format : key, plugin
			//
			std::multimap<std::string, std::string> ctcp_plugins;

			//
			/// \brief Global Privmsg plugins
			/// \note Format : key, plugin
			//
			std::multimap<std::string, std::string> global_privmsg_plugins;

			//
			/// \brief Channel based privmsg plugins
			/// \note Format : <key, channel>, plugin
			//
			std::multimap<std::pair<std::string, std::string>, std::string > channel_privmsg_plugins;

			//
			/// \brief Time we got the last message
			//
			time_t last_message_time;

			//
			/// \brief Our list of masks, and what level they're set to
			//
			std::list <std::pair <std::string, Level> > user_levels;

			//
			/// \brief Have we authed?
			//
			bool has_authed;

			//
			/// \brief The bot's start time
			//
			time_t start_time;
	};

}

#endif // BOT_BOT_H

