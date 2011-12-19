//
/// \file plugins/help/help.cpp
/// \brief Help pluginn
//

#include "help.h"

#include <fstream>
#include <sstream>

#define ENDLINE "<br />" << std::endl

void Help::init (JulieSu::Bot* bot)
{
	this->author = "thothonegan";
	this->name = "Help";
	this->description = "Returns help information";

	this->type = JulieSu::PLUGIN_PRIVMSG;
	
	this->bot = bot;
}

void Help::free (void)
{}

void Help::run (JulieSu::Irc::Message message)
{
	// Respond to their message
	std::string arguments = message.privmsg_msg;
	arguments = arguments.substr(arguments.find(" ")+1);

	outputHTMLTo ("/var/www/juliesu/help.html", message.privmsg_target);

	std::string str; str = "[help] http://www.hackerguild.com/juliesu/help.html";

	if (message.privmsg_target == bot->getName())
		bot->getConnection()->sendPrivMsg (message.nick, str);
	else
		bot->getConnection()->sendPrivMsg (message.privmsg_target, str);
}

void Help::outputHTMLTo (std::string filename, std::string target)
{
	std::ofstream file (filename.c_str());

	file << "<html><head><title>JulieSu::Help</title></head><body>";

	time_t t = time(NULL);
	file << "[help] Generated on : " << ctime (&t) << ENDLINE;

	file << "[help] --- Help ---" << ENDLINE;

	// Grab the plugin manager from our bot
	JulieSu::PluginManager* manager = bot->getPluginManager();

	// RAW plugins
	file << "[help] --- RAW ---" << ENDLINE;

	std::multimap<std::string, std::string> raw_plugins = bot->getRawPlugins ();

	for (std::multimap<std::string, std::string>::iterator iter = raw_plugins.begin(); iter != raw_plugins.end(); ++iter)
	{
		// Format is key, plugin
		std::string key = iter->first;
		std::string plugin_str = iter->second;

		// Grab plugin data from the manager
		JulieSu::Plugin* plugin = manager->getPlugin (plugin_str)->getPlugin();

		file << "[help] " << key << " : " << plugin->getName() << " - " << plugin->getDescription() << ENDLINE;
	}

	// CTCP plugins
	file << "[help] --- CTCP ---" << ENDLINE;

	std::multimap<std::string, std::string> ctcp_plugins = bot->getCtcpPlugins();

	for (std::multimap<std::string, std::string>::iterator iter = ctcp_plugins.begin(); iter != ctcp_plugins.end(); ++iter)
	{
		// Format is key, plugin
		std::string key = iter->first;
		std::string plugin_str = iter->second;

		// Grab plugin data from the manager
		JulieSu::Plugin* plugin = manager->getPlugin (plugin_str)->getPlugin();

		file << "[help] " << key << " : " << plugin->getName() << " - " << plugin->getDescription() << ENDLINE;
	}

	// Global PRIVMSG plugins
	file << "[help] --- Global PRIVMSG ---" << ENDLINE;

	std::multimap<std::string, std::string> global_privmsg_plugins = bot->getGlobalPrivmsgPlugins();

	for (std::multimap<std::string, std::string>::iterator iter = global_privmsg_plugins.begin(); iter != global_privmsg_plugins.end(); ++iter)
	{
		// Format is key, plugin
		std::string key = iter->first;
		std::string plugin_str = iter->second;

		// Grab plugin data from the manager
		JulieSu::Plugin* plugin = manager->getPlugin (plugin_str)->getPlugin();

		file << "[help] " << key << " : " << plugin->getName() << " - " << plugin->getDescription() << ENDLINE;
	}

	// Channel PRIVMSG plugins
        if (target != bot->getName())
	{
		std::string channel = target;

		file << "[help] --- PRIVMSG " << channel << " ---" << ENDLINE;
	
		std::multimap<std::pair<std::string, std::string>, std::string > channel_privmsg_plugins = bot->getChannelPrivmsgPlugins ();
	
		for (std::multimap<std::pair <std::string, std::string>, std::string>::iterator iter = channel_privmsg_plugins.begin(); iter != channel_privmsg_plugins.end(); ++iter)
		{
			// Format is <key, channel> plugin
			std::string key = iter->first.first;
			std::string p_channel = iter->first.second;
			std::string plugin_str = iter->second;
	
			if (channel != p_channel)
				continue; // Not our plugin

			// Grab plugin data from the manager
			JulieSu::Plugin* plugin = manager->getPlugin (plugin_str)->getPlugin();
	
			file << "[help] " << key << " : " << plugin->getName() << " - " << plugin->getDescription() << ENDLINE;
		}
	}

	// Done
	file << "[help] --- End of Help ---" << ENDLINE;

	file << "</body> </html>" << ENDLINE;

	file.close();
}


JulieSu::Plugin* initPlugin (JulieSu::Bot* bot)
{
	JulieSu::Plugin* temp = new Help;
	temp->init (bot);

	return temp;
}

void freePlugin (JulieSu::Plugin* plugin)
{
	plugin->free();

	delete plugin;
}

