//
/// \file plugins/time/source/time.cc
/// \brief Time plugin for JulieSu
//

#include "time.h"
#include <ctime>
#include <sstream>
#include <string>

void Time::Init (JulieSu::Irc::Connection* connection)
{
	this->author = "thothonegan";
	this->name = "Time Plugin";

	this->connection = connection;
}

void Time::Free (void)
{
}

#include <iostream>
void Time::Run (std::string arguments, JulieSu::Irc::Message message)
{
	std::string offset;
	if (arguments[0] == '-')
		offset = arguments.substr(1);
	else
		offset = arguments;

	int offset_hours = atoi (offset.c_str());

	// Calculate the current time (GMT/UTC)
	tm* tm_struct;
	time_t time_temp = time(NULL);
	time_temp += (offset_hours * 60 * 60); // Offset by the number of seconds

	tm_struct = gmtime (&time_temp);
	
	std::stringstream stream;

	// Weekday	
	switch (tm_struct->tm_wday)
	{
		case 0:
			stream << "Sun"; break;

		case 1:
			stream << "Mon"; break;

		case 2:
			stream << "Tue"; break;

		case 3:
			stream << "Wed"; break;

		case 4:
			stream << "Thr"; break;

		case 5:
			stream << "Fri"; break;

		case 6:
			stream << "Sat"; break;

		default:
			stream << "Unk"; break;
	}
	stream << " ";

	switch (tm_struct->tm_mon)
	{
		case 0:
			stream << "Jan"; break;

		case 1:
			stream << "Feb"; break;

		case 2:
			stream << "Mar"; break;

		case 3:
			stream << "Apr"; break;

		case 4:
			stream << "May"; break;

		case 5:
			stream << "Jun"; break;

		case 6:
			stream << "Jul"; break;

		case 7:
			stream << "Aug"; break;

		case 8:
			stream << "Sep"; break;

		case 9:
			stream << "Oct"; break;

		case 10:
			stream << "Nov"; break;

		case 11:
			stream << "Dec"; break;

		default:
			stream << "Unk"; break;
	}
	stream << " ";

	if (tm_struct->tm_mday < 10)
		stream << "0" << tm_struct->tm_mday;
	else
		stream << tm_struct->tm_mday;

	stream << " " << tm_struct->tm_year+1900 << " ";

	if (tm_struct->tm_hour < 10)
		stream << "0" << tm_struct->tm_hour;
	else
		stream << tm_struct->tm_hour;
	stream << ":";

	if (tm_struct->tm_min < 10)
		stream << "0" << tm_struct->tm_min;
	else
		stream << tm_struct->tm_min;
	stream << ":";

	if (tm_struct->tm_sec < 10)
		stream << "0" << tm_struct->tm_sec;
	else
		stream << tm_struct->tm_sec;

	stream << " (GMT";
	if (offset_hours < 0)
		stream << offset_hours;
	else
		stream << "+" << offset_hours;
	stream << ")";

	// Now for beats
	time_t secs_in_day = time_temp % (60*60*24); // Gives us seconds in the day
	int beats = (int) (secs_in_day * .01157);
	stream << " : @" << beats;

	std::string fullmsg = message.nick + " : " + stream.str();
	if (connection->getNickname() == message.privmsg_target)
		connection->Send ("PRIVMSG " + message.nick + " :" + fullmsg);
	else
		connection->Send ("PRIVMSG " + message.privmsg_target + " :" + fullmsg);
}

JulieSu::Plugin* InitPlugin (JulieSu::Irc::Connection* connection)
{
	JulieSu::Plugin* temp = new Time;
	temp->Init(connection);

	return temp;
}

void FreePlugin (JulieSu::Plugin* plugin)
{
	plugin->Free ();
	delete plugin;
}
