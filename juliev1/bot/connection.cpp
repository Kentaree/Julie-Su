//
/// \file bot/source/connection.cpp
/// \brief IRC protocol class
//

#include "connection.h"
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <cstdlib>
#include <cstring>

#include "output.h"

#define IRC_PORT 6667
#define IRC_ENDLINE "\n"

// (char3) + <00000AFM> + (char15) is for kvirc : A = Avatar? F = Female? M = Male?
#define REAL_NAME (char)3 + "6" + (char)15 + "Cyberspace Entity"

namespace JulieSu { namespace Irc
{
	Connection::Connection (const std::string server_name, const std::string nickname, const std::string nickserv_password)
	{
		this->socket = ::socket(AF_INET, SOCK_STREAM, 0);
		int yes = true;
		setsockopt (this->socket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));
	
		// Translate the hostname
		hostent* remote_host = gethostbyname (server_name.c_str());
		if (!remote_host)
		{
			Output::write ("Error : gethostbyname() failed!");
			throw "Exception";
		}
	
		char* ip_address = inet_ntoa (* ((in_addr*) remote_host->h_addr));
	
		sockaddr_in destination_address;
		destination_address.sin_family = AF_INET;
		destination_address.sin_port = htons (IRC_PORT);
		destination_address.sin_addr.s_addr = inet_addr (ip_address);
		memset (&(destination_address.sin_zero), '\0', 8);
	
		connect (this->socket, (sockaddr*) &destination_address, sizeof(sockaddr));
	
		// Now we register
		this->send ("USER " + nickname + " . . :" + REAL_NAME);
		this->send ("NICK " + nickname);
	
		this->nickpass = nickserv_password;

		this->nickname = nickname;
	}
	
	Connection::~Connection (void)
	{
		close (this->socket);
	}
	
	void Connection::initLogin (void)
	{
		// Identify
		this->send ("PRIVMSG NickServ IDENTIFY " + nickpass);
	
		// we are a bot!
		this->send ("MODE " + nickname + " +B");

		sleep (1); // Let it catch up to us
	}

	void Connection::joinChannel (std::string channel)
	{
		this->send ("JOIN " + channel);
	}
	
	void Connection::send (const std::string message)
	{
		Output::write ("[MSG SENT] " + message);
		::send (this->socket, message.c_str(), message.size(), 0);
		::send (this->socket, IRC_ENDLINE, 1, 0);
	}
	
	std::string Connection::receive (void)
	{
		char buffer[4096];
	
		// Clean the buffer
		memset (buffer, '\0', sizeof(buffer));
	
		// Time to wait
		timeval tv;
		fd_set fds;
		
		tv.tv_sec = 0;
		tv.tv_usec = 500;
	
		FD_ZERO (&fds);
		FD_SET (this->socket, &fds);
	
		select (this->socket+1, &fds, NULL, NULL, &tv);
	
		if (FD_ISSET(this->socket, &fds))
			recv (this->socket, buffer, sizeof(buffer), 0);
	
		return std::string (buffer);
	}
	
	Message Connection::parse( std::string message)
	{
		return JulieSu::Irc::Message (message);
	}
	
	std::string Connection::getNickname (void)
	{
		return nickname;
	}

	void Connection::sendPrivMsg (std::string target, std::string message)
	{
		send("PRIVMSG " + target + " :" + message);
	}

	void Connection::sendCtcpResponse (std::string target, std::string message)
	{
		send ("NOTICE " + target + " :\001" + message + "\001");
	}

}}
