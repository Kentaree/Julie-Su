//
/// \file bot/source/main.cpp
/// \brief Main function for Julie-Su
//

#include <cstdlib>
#include <ctime>
#include <fstream>

#include "config.h"
#include "connection.h"
#include "global.h"
#include "output.h"

int main (int argc, char** argv)
{
	if (argc == 1)
	{
		JulieSu::Output::write ("Pass the config file!");
		return 0;
	}

	JulieSu::argc = argc;
	JulieSu::argv = argv;

	JulieSu::Config::loadConfig (argv[1]);

	while (true)
	{
		try
		{

			JulieSu::Output::write ("Trying to connect");

			for (int x=0; x < JulieSu::Config::bots.size(); ++x)
				JulieSu::Config::bots[x]->connect();

			while (true)
			{
					for (int x=0; x < JulieSu::Config::bots.size(); ++x)
						JulieSu::Config::bots[x]->processMessages();

				timespec tv; tv.tv_sec = 0; tv.tv_nsec = 1000000 * 1;
				nanosleep(&tv, NULL);
			}
		}
		catch (...)
		{
			sleep (10);
		}
	}

	return EXIT_SUCCESS;
}
