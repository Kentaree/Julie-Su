//
/// \file bot/source/plugin.h
/// \brief A plugin class
//

#ifndef BOT_SOURCE_PLUGIN_H
#define BOT_SOURCE_PLUGIN_H

#include <string>

#include "bot.h"
#include "output.h"

namespace JulieSu
{

	// Plugin types
	enum PluginType
	{
		PLUGIN_RAW, ///< Raw plugin : listens for commands directory
		PLUGIN_CTCP, ///< CTCP plugin : listens for CTCP commands
		PLUGIN_PRIVMSG ///< PRIVMSG plugin : listens via PRIVMSG
	};

	//
	/// \brief Derivable plugin class
	//
	class Plugin
	{
		public:
			Plugin (void);
			virtual ~Plugin (void);

			virtual void run (JulieSu::Irc::Message message) = 0;
			virtual void init (JulieSu::Bot* bot) = 0;
			virtual void free (void) = 0;

			virtual void loop (void);

			PluginType getType (void);

			std::string getAuthor (void);
			std::string getName (void);
			std::string getDescription (void);

		protected:
			std::string author; ///< Author of the plugin
			std::string name; ///< Name of the plugin
			std::string description; ///< Description of the plugin

			PluginType type; ///< Type of plugin

			Bot* bot; ///< IRC bot
	};

}

#endif // BOT_SOURCE_PLUGIN_H
