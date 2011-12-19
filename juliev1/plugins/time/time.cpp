//
/// \file plugins/time/time.cpp
/// \brief Time plugin
//

#include "time.h"
#include <ctime>
#include <sstream>
#include <string>
#include <cstdlib>

std::vector<std::pair<std::string, int> > name_to_timezone;

void Time::init (JulieSu::Bot* bot)
{
	this->author = "thothonegan";
	this->name = "Time";
	this->description = "Returns the time for a given timezone or user";

	this->type = JulieSu::PLUGIN_PRIVMSG;
	
	this->bot = bot;
}

void Time::free (void)
{}

void Time::run (JulieSu::Irc::Message message)
{
	// Respond to their message
	std::string arguments = message.privmsg_msg;
	arguments = arguments.substr(arguments.find(" ")+1);

	bool set = false;

	std::string offset;

	if (arguments.size() < 1)
		offset = "         ";
	else
		offset = arguments; // Ignore beginning space

	if (offset[0] == 's' && offset[1] == 'e' && offset[2] == 't')
		set = true;

	if (!set)
	{

		// First check if its a name we have in our table
		std::string name = offset.substr(0, offset.find(' '));

		int offset_hours;

		bool found = false;
		for (int x=0; x < name_to_timezone.size(); ++x)
		{
			//std::cout << "CHECK : [" << name_to_timezone[x].first << "] vs [" << name << "]" << std::endl;
			if (name_to_timezone[x].first == name)
			{
				found = true;
				offset_hours = name_to_timezone[x].second;
				break;
			}
		}

		if (!found)
			offset_hours = atoi (offset.c_str());
	
		// Calculate the current time (GMT/UTC)
		tm* tm_struct;
		time_t time_temp = time(NULL);
		time_temp += (offset_hours * 60 * 60); // Offset by the number of seconds
	
		// For beats
		time_t time_temp_beats = time(NULL);
		time_temp_beats += (1 * 60 * 60);
	
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
	
		stream << " (UTC";
		if (offset_hours < 0)
			stream << offset_hours;
		else
			stream << "+" << offset_hours;
		stream << ")";
	
		// Now for beats
		time_t secs_in_day = time_temp_beats % (60*60*24); // Gives us seconds in the day
		int beats = (int) (secs_in_day * .01157);
		stream << " : @" << beats;
	
		std::string fullmsg = message.nick + " : " + stream.str();
		if (message.privmsg_target == bot->getName())
			bot->getConnection()->sendPrivMsg (message.nick, fullmsg);
		else
			bot->getConnection()->sendPrivMsg (message.privmsg_target, fullmsg);
	} // End !set
	else
	{
		// Set!
		// First skip the set command (' set ')
		if (arguments.size() < 5)
			return;

		offset = arguments.substr (5);

		// Second is the name (till next space)
		if (offset.find(' ') == std::string::npos)
			return;

		std::string name = offset.substr (0, offset.find(' '));
		offset = offset.substr (offset.find(' ')+1);

		// Third is the timezone
		int offset_hours;
		if (offset[0] == '-')
			offset_hours = (-1) * atoi (offset.substr(1).c_str());
		else
			offset_hours = atoi (offset.c_str());

		// Now write to our array
		std::pair <std::string, int> temp;
		temp.first = name;
		temp.second = offset_hours;
		bool done = false;

		for (int x=0; x < name_to_timezone.size(); ++x)
		{

			if (name_to_timezone[x].first == temp.first)
			{
				name_to_timezone[x].second = temp.second;
				done = true;
			}
		}

		if (done)
		{
			std::stringstream fullmsg;
			fullmsg << message.nick + " : Timezone changed to : " << offset_hours;
			if (message.privmsg_target == bot->getName())
				bot->getConnection()->sendPrivMsg (message.nick, fullmsg.str());
			else
				bot->getConnection()->sendPrivMsg (message.privmsg_target, fullmsg.str());		}
		else
		{
			// Add it
			name_to_timezone.push_back (temp);

			std::stringstream fullmsg;
			fullmsg << message.nick + " : Timezone added as : " << offset_hours;
			if (message.privmsg_target == bot->getName())
				bot->getConnection()->sendPrivMsg (message.nick, fullmsg.str());
			else
				bot->getConnection()->sendPrivMsg (message.privmsg_target, fullmsg.str());		}
	} // set

}


JulieSu::Plugin* initPlugin (JulieSu::Bot* bot)
{
	JulieSu::Plugin* temp = new Time;
	temp->init (bot);

	return temp;
}

void freePlugin (JulieSu::Plugin* plugin)
{
	plugin->free();

	delete plugin;
}

