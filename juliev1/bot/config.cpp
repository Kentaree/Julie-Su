//
/// \file bot/config.cpp
/// \brief Config
//

#include "config.h"
#include <fstream>
#include <map>
#include "output.h"

namespace JulieSu { namespace Config
{
	// Globals - Defaults
	JulieSu::Bot* current_bot = NULL;
	std::string current_channel = "";
	std::vector<JulieSu::Bot*> bots;

	void loadConfig (std::string filename)
	{
		XML_Parser parser = XML_ParserCreate ("UTF-8");
		XML_SetElementHandler (parser, startXML, endXML);

		std::ifstream file (filename.c_str());

		std::string line;
		
		while (!file.eof())
		{
			getline(file, line);
			XML_Parse (parser, line.c_str(), line.size(), false);
		}

		// Done
		XML_Parse (parser, line.c_str(), 0, true);

	}

	void startXML (void* userData, const XML_Char* name,
			const XML_Char** atts)
	{
		// Convert to something easier to use
		std::string strname = name;
		std::map<std::string, std::string> map;

		const char** position = atts;
		while (*position != NULL)
		{
			// Name and attribute
			const char* name = *position;
			position++;
			const char* attribute = *position;
			position++;

			// Add
			map[name]=attribute;
		}

		// <config>
		if (strname == "config")
		{}

		// <bot>
		else if (strname == "bot")
		{
			// Accepted attributes
			// name : name of the bot
			// password : nickserv password of the bot
		
			bots.push_back(new JulieSu::Bot (map["name"], map["password"]));
			current_bot = bots[bots.size()-1];
		}

		// <server>
		else if (strname == "server")
		{
			// Accepted attributes
			// hostname : Hostname of the IRC server
			// port : The port of the IRC server (optional)
			if (map["port"] == "")
				map["port"] = "6667";

			current_bot->setServer (map["hostname"], atoi (map["port"].c_str()));
		}

		// <channel>
		else if (strname == "channel")
		{
			// Attributes
			// name : Name of the channel
			current_bot->addChannel(map["name"]);
			current_channel = map["name"];
		}

		// <plugin>
		else if (strname == "plugin")
		{
			// Attributes
			// name : Name of the plugin
			// location : Location of the plugin
			current_bot->loadPlugin(map["name"], map["location"]);
		}

		// <link>
		else if (strname == "link")
		{
			// Attributes
			// plugin : Name of the plugin we are linking
			// key : Key to set off the plugin (what sets it off is determined by the plugin type)

			// Slightly different depending if we're in a channel or not
			/// \todo Lets skip channel for now
			if (current_channel == "")
			{
				// Server wide plugin
				// As such, we need to add it to the global link list
				// and link it to its mount point
				// Later this should be per server
				current_bot->linkPlugin (map["plugin"], map["key"]);
			}
			else
			{
				// Channel plugin
				current_bot->linkPlugin (map["plugin"], map["key"], current_channel);
			}
		}

		// <setlevel>
		else if (strname =="setlevel")
		{
			// Attributes
			// mask : the mask to be matched (IRC mask)
			// level : the level to set the user
			current_bot->setLevel (map["mask"], JulieSu::levelFromString (map["level"]));
		}

		else
		{
			Output::write ("-- Tag Start : " + std::string(name));
		}
	}

	void endXML (void* userData, const XML_Char* name)
	{
		std::string strname = name;

		// </config>
		if (strname == "config")
		{}

		// </bot>
		else if (strname == "bot")
		{
			// End this current bot
			current_bot = NULL;
		}

		// </server>
		else if (strname == "server")
		{}

		// </channel>
		else if (strname == "channel")
		{
			current_channel = "";
		}

		// </plugin>
		else if (strname == "plugin")
		{}

		// </link>
		else if (strname == "link")
		{}

		// </setlevel>
		else if (strname == "setlevel")
		{}

		else
		{
			Output::write ("-- Tag End : " + std::string(name));
		}
	}

} }

