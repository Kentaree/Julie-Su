//
/// \file boot/source/message.cpp
/// \brief Message class for IRC Parsing
//

#include "message.h"

#include <iostream>

JulieSu::Irc::Message::Message (std::string message)
{
	// Remove newlines
	if (message.find("\r") != std::string::npos)
		message.erase (message.find("\r"));

	// Parse the message
	
	// First we need to check if its PING, very different layout
	if (message.substr(0,4) == "PING")
	{
		// Command is ping
		this->command = "PING";

		// Data is rest (check if theirs a : there, dont want)
		if (message.substr(5,1) == ":")
		{
			data = message.substr (6);
		}
		else
		{
			data = message.substr (5); // No : so dont worry
		}
	}

	// Or ERROR
	else if (message.substr(0, 5) == "ERROR")
	{
		// Command is error
		this->command = "ERROR";

		// Data is rest (check if theirs a : there, dont want)
		if (message.substr(5,1) == ":")
		{
			data = message.substr (6);
		}
		else
		{
			data = message.substr (5); // No : so dont worry
		}
	}

	// Standard parsing for other messages
	else if (message.substr(0,1) == ":")
	{
		// Beginning of string is host
		// Find the space
		int first_space = message.find(" ");

		// Grab the host
		userhost = message.substr (1, first_space - 1);

		// Split the userhost and grab the host
		host = userhost.substr (userhost.find("@")+1);

		// Parse the username out of the host
		username = userhost.substr (userhost.find("!")+1, userhost.find("@")-userhost.find("!")-1);

		// Now lets parse the nick out of the host
		nick = message.substr (1, message.find ("!") - 1);

		// Now we find a space after that one
		int second_space = message.find (" ", first_space + 1);

		// This should be the command (between the two spaces)
		command = message.substr (first_space + 1, second_space - first_space - 1);

		// And the rest is data (Includes : if one)
		data = message.substr (second_space+2);
		
		// Now message specific parsing
		// PRIVMSG
		if (this->command == "PRIVMSG")
		{
			// The target is the first part of the data
			int third_space = message.find (" ", second_space + 1);

			// This is target (channel/privmsg)
			privmsg_target = message.substr (second_space + 1, third_space - second_space - 1);

			// Rest should be the message itself (take out :)
			if (message.substr (third_space+1, 1) == ":")
			{
				privmsg_msg = message.substr (third_space+2);
			}
			else
			{
				privmsg_msg = message.substr (third_space+1);
			}
		}
	}

	else
	{
		// Not parsed
		data = message;
	}
}
