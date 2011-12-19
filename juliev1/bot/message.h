//
/// \brief bot/source/message.h
/// \brief Parsed IRC message class
//

#ifndef BOT_SOURCE_MESSAGE_H
#define BOT_SOURCE_MESSAGE_H

#include <string>

namespace JulieSu
{
	namespace Irc
	{
		class Message
		{
			public:
				//
				/// \brief Create a parsed message
				/// \param message The message to parse
				//
				Message (std::string message);

				std::string userhost; ///< The host the message was from
				std::string nick; ///< The nick who said it
				std::string username; ///< The username of an IRC host (nick!username@host)
				std::string host; ///< The host the message was sent from
				std::string command; ///< The command
				std::string data; ///< The data sent

				// Specialized
				std::string privmsg_target; ///< PRIVMSG : The channel/nickname we heard it in
				std::string privmsg_msg; ///< PRIVMSG : The message
		};
	}
}

#endif // BOT_SOURCE_MESSAGE_H
