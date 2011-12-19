//
/// \file bot/config.h
/// \brief Config handling namespace 
//

#ifndef BOT_CONFIG_H
#define BOT_CONFIG_H

#include <string>
#include <vector>

#include <expat.h>

#include "bot.h"

namespace JulieSu
{
	namespace Config
	{
			//
			/// \brief Load the config
			/// \param filename Filename to read the config from
			//
			void loadConfig (std::string filename);

			//
			/// \brief Called on start of an XML tag
			/// \param userData user specific data (none)
			/// \param name The name of the tag
			/// \param atts Attributes
			//
			void XMLCALL startXML (void* userData, const XML_Char* name,
					const XML_Char** atts);

			//
			/// \brief Called on end of an XML tag
			/// \param userData user specific data (none)
			/// \param name The name of the tag
			//
			void XMLCALL endXML (void* userData, const XML_Char* name);

			// CONFIG INFO

			//
			/// \brief Bots controlled by JS
			//
			extern std::vector<JulieSu::Bot*> bots;

			//
			/// \brief The current bot being configed
			//
			extern JulieSu::Bot* current_bot;

			//
			/// \brief The current channel being confgured
			//
			extern std::string current_channel;

	};
}

#endif

