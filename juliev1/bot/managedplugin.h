//
/// \file bot/source/managedplugin.h
/// \brief A plugin managed by JS
//

#ifndef BOT_SOURCE_MANAGEDPLUGIN_H
#define BOT_SOURCE_MANAGEDPLUGIN_H

#include <string>

#include "message.h"

namespace JulieSu
{
	class Bot;
	class Plugin;

	class ManagedPlugin
	{
		public:
			//
			/// \brief Load the new plugin
			/// \param name The name the plugin is linked to
			/// \param filename The plugin filename
			/// \param bot The bot the plugin will use
			//
			ManagedPlugin (std::string name, std::string filename, JulieSu::Bot* bot);

			//
			/// \brief Unload the plugin
			//
			virtual ~ManagedPlugin (void);

			//
			/// \brief Get the name
			//
			std::string getName (void);

			//
			/// \brief Get the plugin's type
			//
			int getType (void);

			//
			/// \brief Runs the plugin
			/// \param message The message for the plugin
			//
			void run (JulieSu::Irc::Message message);

			//
			/// \brief Loop the plugin
			//
			void loop (void);

			//
			/// \brief Get the raw plugin to run queries on it : DONT MESS WITH MUCH
			//
			JulieSu::Plugin* getPlugin (void);

		protected:
			JulieSu::Plugin* plugin; ///< The Plugin Itself
			std::string filename; ///< The file the plugin was loaded from
			std::string name; ///< The command used to call the plugin
			void* dl_handle; ///< The dynamic library handle

			JulieSu::Bot* bot; ///< Bot the plugin is using
	};
}

#endif // BOT_SOURCE_MANAGEDPLUGIN_H 
