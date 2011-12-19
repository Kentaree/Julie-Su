//
/// \file bot/pluginmanager.h
/// \brief Manager of plugins
//

#ifndef BOT_PLUGINMANAGER_H
#define BOT_PLUGINMANAGER_H

#include <string>
#include <vector>

#include "managedplugin.h"

namespace JulieSu
{
	class Bot;

	class PluginManager
	{
		public:
			//
			/// \brief Constructor
			/// \param bot The bot this pluginmanager is a part of
			//
			PluginManager (JulieSu::Bot* bot);
			
			//
			/// \brief Destructor
			//
			~PluginManager (void);

			//
			/// \brief Loads a plugin
			/// \param name The name of the plugin
			/// \param location The location of the plugin
			//
			void loadPlugin (std::string name, std::string location);

			//
			/// \brief Get a specific plugin
			/// \param name The name of the plugin
			/// \return The plugin
			//
			JulieSu::ManagedPlugin* getPlugin (std::string name);

			//
			/// \brief Runs a plugin
			/// \param name The name of the plugin to run
			/// \param message The message received that the plugin should handle
			//
			void runPlugin (std::string name, JulieSu::Irc::Message message);

			//
			/// \brief Loop all plugins
			//
			void loopPlugins (void);

		protected:
			//
			/// \brief The bot this manager is a part of
			//
			JulieSu::Bot* bot;

			//
			/// \brief Plugins loaded
			//
			std::vector <JulieSu::ManagedPlugin*> plugins;
	};

}

#endif // BOT_PLUGINMANAGER_H

