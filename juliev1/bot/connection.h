//
/// \file bot/source/connection.h
/// \brief IRC protocol class
//

#ifndef BOT_SOURCE_CONNECTION_H
#define BOT_SOURCE_CONNECTION_H

#include <string>
#include <vector>

#include "message.h"

namespace JulieSu
{
	namespace Irc
	{
		class Connection
		{
			public:
				//
				/// \brief Connects to an IRC server
				/// \param server_name The name of the server (DNS)
				/// \param nickname The name the bot will use
				/// \param nickserv_password The password the bot uses with nickserv
				//
				Connection (const std::string server_name, const std::string nickname, const std::string nickserv_password);

				//
				/// \brief Disconnects from the server
				//
				virtual ~Connection ();

				//
				/// \brief Initilizes the login : talks to NickServ, joins channels, etc
				//
				void initLogin (void);

				//
				/// \brief Join a channel
				/// \param name The channel name
				//
				void joinChannel (std::string channel);

				//
				/// \brief Send an IRC message RAW
				/// \param message The raw IRC message
				//
				void send (const std::string message);

				//
				/// \brief Receive a line from IRC
				/// \return The message
				//
				std::string receive (void);

				//
				/// \brief Parses a string into an IRC message
				/// \return The IRC message
				//
				JulieSu::Irc::Message parse (std::string message);

				//
				/// \brief Gets our nick
				/// \return Our nick
				//
				std::string getNickname (void);

				//
				/// \brief Sends a private message to a target
				/// \param target The target to send the mesage to
				/// \param message the message to send
				//
				void sendPrivMsg (std::string target, std::string message);

				//
				/// \brief Sends a CTCP response message to a araget
				/// \param target The target to send the message to
				/// \param message The message to send
				//
				void sendCtcpResponse (std::string target, std::string message);

			protected:
				int socket; ///< The network socket

				std::string nickname;
				std::string nickpass;

				char bufffer[4096];
		};
	}
}

#endif // BOT_SOURCE_CONNECTION_H
