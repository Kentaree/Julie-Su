//
/// \file bot/pluginmanager.cpp
/// \brief Pluginmanager
//

#include "pluginmanager.h"

namespace JulieSu
{
	PluginManager::PluginManager (JulieSu::Bot* bot)
	{
		this->bot = bot;
	}

	PluginManager::~PluginManager (void)
	{}

	void PluginManager::loadPlugin (std::string name, std::string location)
	{
		plugins.push_back (new JulieSu::ManagedPlugin (name, location, bot));
	}

	JulieSu::ManagedPlugin* PluginManager::getPlugin (std::string name)
	{
		for (int x=0; x < plugins.size(); ++x)
		{
			if (plugins[x]->getName() == name)
				return plugins[x];
		}
	}

	void PluginManager::runPlugin (std::string name, JulieSu::Irc::Message message)
	{
		getPlugin(name)->run (message);
	}

	void PluginManager::loopPlugins (void)
	{
		for (int x=0; x < plugins.size(); ++x)
		{
			plugins[x]->loop();
		}
	}
}

