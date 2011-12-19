//
/// \file bot/source/managedplugin.cpp
/// \brief A plugin managed by JS
//

#include "managedplugin.h"
#include <dlfcn.h>

#include <cstdlib>

#include "output.h"
#include "plugin.h"

namespace JulieSu
{
	JulieSu::ManagedPlugin::ManagedPlugin (std::string name, std::string filename, JulieSu::Bot* bot)
	{
		// Load the plugin
		dl_handle = dlopen (filename.c_str(), RTLD_LAZY);
	
		const char* error = dlerror();
		if (error)
		{
			Output::write ("DLError :"  + std::string(error));
			exit(1);
		}
	
		
		JulieSu::Plugin* (*InitPlugin) (JulieSu::Bot* bot);
			*(void **) (&InitPlugin) = dlsym (dl_handle, "initPlugin");
		
		error = dlerror();
		if (error)
		{
			Output::write ("DLError : " + std::string(error));
			exit (1);
		}

		plugin = (*InitPlugin)(bot);
	
		Output::write ("Plugin Loaded : " + name);
		this->name = name;
	
		this->bot = bot; // Set the connection
	}

	ManagedPlugin::~ManagedPlugin (void)
	{
		Output::write ("Plugin Freed");
	
		// Delete the object
		void (*FreePlugin) (JulieSu::Plugin*);
		*(void **) (&FreePlugin) = dlsym (dl_handle, "freePlugin");
	
		const char* error = dlerror();
		if (error)
		{
			Output::write ("DLError : " + std::string(error));
			exit (1);
		}
	
		(*FreePlugin)(plugin);
	
		// Close the plugin
		dlclose (dl_handle);
	}

	std::string ManagedPlugin::getName (void)
	{
		return name;
	}

	int ManagedPlugin::getType (void)
	{
		return plugin->getType();
	}

	void ManagedPlugin::run (JulieSu::Irc::Message message)
	{
		plugin->run (message);
	}

	void ManagedPlugin::loop (void)
	{
		plugin->loop();
	}

	Plugin* ManagedPlugin::getPlugin (void)
	{
		return plugin;
	}
}
